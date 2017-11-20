#!/usr/bin/python3

'''
HC-12 Mux
Allows multiple clients to send or receive.
Automatically performs HC-12 baud rate switching.
'''

import functools
import logging
import selectors
import socket

import yaml
import serial

import protocol


def protocol_checksum(message):
	return message + bytes([functools.reduce(int.__xor__, message)])

class Mux:
	def __init__(self):
		self.interfaces = {}
		self.routes = {}
		self.selector = selectors.DefaultSelector()

	def get_interface(self, id):
		return self.interfaces.get(id)

	def add_interface(self, interface):
		self.interfaces[interface.id] = interface
		interface.register(self)

	def add_route(self, source, sink):
		self.routes.setdefault(source, set()).add(sink)

	def distribute(self, source, data):
		for sink in self.routes.get(source, ()):
			sink.write(data)

	def run(self):
		while True:
			for key, events in self.selector.select():
				key.read(key.fdo, events, self)

class Decoder:
	def __init__(self):
		self.buf = bytearray()
		self.debug_buf = bytearray()

	def decode(self, data):
		self.buf.extend(data)
		while len(self.buf) > 0:
			plen = protocol.radio_packet_size(self.buf[0])
			if plen is not None:
				if len(self.buf) < plen + 1:
					return
				packet = self.buf[:plen]
				cksum = self.buf[plen]
				#verify
				cs = protocol_checksum(packet)
				if cksum == cs:
					self.buf = self.buf[plen+1:]
					yield from protocol.radio_packet_parse(packet)
					continue
			self.buf = self.buf[1:]


class Encoder:
	def __init__(self):
		pass

	def encode(self, message):
		if message["type"] == "debug":
			text = message["message"].encode()
			for i in range(0, len(text), 16):
				yield protocol.radio_packet_pack({"_type": "debug", "message": message[i:i+16]})
		else:
			yield protocol.radio_packet_pack(message)


class Interface:
	def __init__(self, config):
		self.id = config['name']
		self.logger = logging.getLogger(self.id)
		self.decoder = Decoder()
		self.encoder = Encoder()

	def register(self, mux):
		pass

	def read(self, fdo, events, mux):
		packet = self._raw_read(fdo, events, mux)
		for message in self.decoder.decode(packet):
			self.logger.getChild('in').debug(message)
			mux.distribute(self, message)

	def write(self, message):
		self.logger.getChild('out').debug(message)
		for packet in self.encoder.encode(message):
			self._raw_write(packet)

	def _raw_read(self, fdo, events, mux):
		raise NotImplementedError()

	def _raw_write(self, message):
		raise NotImplementedError()


class InterfaceUDPBroadcast(Interface):
	def __init__(self, config):
		super().__init__(config)
		self.port = config['port']
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.bind(('', self.port))

	def register(self, mux):
		mux.selector.register(self.sock, selectors.EVENT_READ)

	def _raw_write(self, data):
		self.sock.sendto(('255.255.255.255', self.port), data)

	def _raw_read(self, fdo, events, mux):
		packet, _ = self.sock.recvfrom(4096)
		return packet


class InterfaceSerial(Interface):
	def __init__(self, config):
		super().__init__(config)
		self._radio_lock = False
		self._receivers = []
		self._recevier_fds = {}
		for interface in config['receivers']:
			ser = serial.Serial(interface['path'], interface['uart_baud'], timeout=0)
			ser.open()
			self._program(ser, "AT+B{:d}\r\nAT+C{:02d}\r\n".format(interface['radio_baud'], interface['radio_channel']))
			self._receivers.append(ser)
			self._recevier_fds[ser.fd] = ser

		sender = config['sender']
		self._sender = serial.Serial(sender['path'], sender['uart_baud'], timeout=0)
		self._program(self._sender, "AT+B{:d}\r\nAT+C{:02d}\r\n".format(sender['radio_baud'], sender['radio_channel']))

		self._lock = config['lock']

	def _program(self, ser, commands):
		ser.dtr = False
		#ser.baudrate = program_baud
		ser.write(commands.encode())
		#ser.baudrate = radio_baud
		ser.dtr = True

	def register(self, mux):
		for fd in self._recevier_fds:
			mux.selector.register(fd, selectors.EVENT_READ)

	def _raw_read(self, fdo, events, mux):
		receiver = self._recevier_fds[fdo]
		return receiver.read(0xffff)

	def write(self, message):
		if message['_type'] == '_mux_radio_lock':
			self.set_radio_lock(message['lock'])
		elif message['_type'] == '_mux_radio_baud':
			self.set_radio_baud(message['baud'])
		elif message['_type'] == '_mux_radio_channel':
			self.set_radio_channel(message['channel'])
		else:
			super().write(message)

	def _raw_write(self, packet):
		self._sender.write(packet)

	def set_radio_lock(self, lock):
		self._radio_lock = lock
		self.logger.getChild('ctrl').debug("set_radio_lock: {}".format(self._radio_lock))

	def set_radio_baud(self, baud):
		if self._radio_lock:
			self.logger.getChild('ctrl').debug("set_radio_baud: Radio locked, ignoring")
			return
		self._sender.dtr = False
		self._sender.write('AT+B{:d}'.format(baud))
		self._baud = baud
		self.logger.getChild('ctrl').debug("set_radio_baud: {}".format(self._baud))
		self._sender.dtr = True

	def set_radio_channel(self, channel):
		if self._radio_lock:
			self.logger.getChild('ctrl').debug("set_radio_channel: Radio locked, ignoring")
			return
		self._sender.dtr = False
		self._sender.write('AT+C{:03d}'.format(channel))
		self._channel = channel
		self.logger.getChild('ctrl').debug("set_radio_channel: {}".format(self._channel))
		self._sender.dtr = True
		pass


class InterfaceSerialSingle(InterfaceSerial):
	def __init__(self, config):
		Interface.__init__(self, config)
		self._radio_lock = False

		interface = config['interface']
		self._serial = serial.Serial(interface['path'], interface['uart_baud'], timeout=0)
		self._program(self._serial, "AT+B{:d}\r\nAT+C{:02d}\r\n".format(interface['radio_baud'], interface['radio_channel']))
		self._lock = config['lock']

	def register(self, mux):
		mux.selector.register(self._serial.fd, selectors.EVENT_READ)

	def _raw_read(self, fdo, events, mux):
		return self._serial.read(0xffff)

	def _raw_write(self, packet):
		self._serial.write(packet)


def listify(x):
	if isinstance(x, list):
		return x
	return [x]


def main():
	import argparse
	ap = argparse.ArgumentParser()
	ap.add_argument("--config")
	args = ap.parse_args()

	with open(args.config, 'r') as f:
		config = yaml.load(f)

	mux = Mux()

	for interface in config['interfaces']:
		if interface['type'] == 'serial':
			iface = InterfaceSerial(interface)
			mux.add_interface(iface)
		elif interface['type'] == 'serial_single':
			iface = InterfaceSerialSingle(interface)
			mux.add_interface(iface)
		elif interface['type'] == 'udp_broadcast':
			iface = InterfaceUDPBroadcast(interface)
			mux.add_interface(iface)
		else:
			raise ValueError("Invalid source type")

	for route in config['routes']:
		for source in listify(route['source']):
			for sink in listify(route['sink']):
				mux.add_route(mux.get_interface(source), mux.get_interface(sink))

	mux.run()

if __name__ == '__main__':
	main()