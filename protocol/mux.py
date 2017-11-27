#!/usr/bin/python3

'''
HC-12 Mux
Allows multiple clients to send or receive.
Automatically performs HC-12 baud rate switching.
'''

import functools
import json
import logging
import logging.config
import selectors
import socket
import sys

import yaml
import serial

import protocol


def protocol_checksum(message):
	return bytes([functools.reduce(int.__xor__, message)])

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
				print(key.data, events)
				key.data.read(key.fileobj, events, self)

class Decoder:
	def __init__(self):
		self.buf = bytearray()
		self.debug_buf = bytearray()

	def decode(self, data):
		self.buf.extend(data)
		while len(self.buf) > 0:
			plen = protocol.radio_packet_size(bytes(self.buf[0:1])) + 1
			if plen is not None:
				if len(self.buf) < plen + 1:
					return
				packet = self.buf[:plen]
				cksum = self.buf[plen:plen+1]
				#verify
				cs = protocol_checksum(packet)
				if cksum == cs:
					self.buf = self.buf[plen+1:]
					message = protocol.radio_packet_parse(packet)
					#TODO: debug
					yield message
					continue
			self.buf = self.buf[1:]


class Encoder:
	def __init__(self):
		pass

	def encode(self, message):
		if message.get("_type", None) == "debug":
			text = message["message"].encode()
			for i in range(0, len(text), 16):
				yield protocol.radio_packet_pack({"_type": "debug", "message": message[i:i+16]})
		else:
			packet = protocol.radio_packet_pack(message)
			packet += bytes((protocol_checksum(packet)))
			yield packet


class Interface:
	def __init__(self, config):
		self.id = config['name']
		self.logger = logging.getLogger(self.id)

	def register(self, mux):
		pass

	def read(self, fdo, events, mux):
		message = self._raw_read(fdo, events, mux)
		self.logger.getChild('in').debug(message)

	def write(self, message):
		self.logger.getChild('out').debug(message)
		self._raw_write(message)

	def _raw_read(self, fdo, events, mux):
		raise NotImplementedError()

	def _raw_write(self, message):
		raise NotImplementedError()


class InterfaceUDPBroadcast(Interface):
	def __init__(self, config):
		super().__init__(config)
		self.port = config['port']
		self.bind = config['bind']
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1) 
		self.sock.bind((self.bind, self.port))

	def register(self, mux):
		mux.selector.register(self.sock, selectors.EVENT_READ, self)

	def read(self, fdo, events, mux):
		print("read")
		packet = self._raw_read(fdo, events, mux)
		message = json.loads(packet.decode())
		self.logger.getChild('in').debug(message)
		mux.distribute(self, message)

	def write(self, message):
		self.logger.getChild('out').debug(message)
		packet = json.dumps(message).encode()
		self._raw_write(packet)

	def _raw_write(self, data):
		self.sock.sendto(data, ('255.255.255.255', self.port))

	def _raw_read(self, fdo, events, mux):
		packet, addr = self.sock.recvfrom(4096)
		if addr != self.sock.getsockname():
			return packet


class InterfaceSerial(Interface):
	def __init__(self, config):
		super().__init__(config)
		self._radio_lock = False
		self._receivers = []
		for interface in config['receivers']:
			ser = serial.Serial(interface['path'], interface['uart_baud'], timeout=0)
			self._program(ser, "AT+B{:d}AT+C{:03d}".format(interface['radio_baud'], interface['radio_channel']))
			self._receivers.append(ser)

		sender = config['sender']
		self._sender = serial.Serial(sender['path'], sender['uart_baud'], timeout=0)
		self._program(self._sender, "AT+B{:d}AT+C{:03d}".format(sender['radio_baud'], sender['radio_channel']))

		self._lock = config['lock']
		self.decoder = Decoder()
		self.encoder = Encoder()

	def _program(self, ser, commands):
		ser.dtr = False
		#ser.baudrate = program_baud
		ser.write(commands.encode())
		#ser.baudrate = radio_baud
		ser.dtr = True

	def register(self, mux):
		for receiver in self._receivers:
			mux.selector.register(receiver, selectors.EVENT_READ, self)

	def read(self, fdo, events, mux):
		packet = self._raw_read(fdo, events, mux)
		for message in self.decoder.decode(packet):
			self.logger.getChild('in').debug(message)
			mux.distribute(self, message)

	def write(self, message):
		if message['_type'] == '_mux_radio_lock':
			self.set_radio_lock(message['lock'])
		elif message['_type'] == '_mux_radio_baud':
			self.set_radio_baud(message['baud'])
		elif message['_type'] == '_mux_radio_channel':
			self.set_radio_channel(message['channel'])
		elif message['_type'] == '_mux_headsup':
			pass
		else:
			self.logger.getChild('out').debug(message)
			for packet in self.encoder.encode(message):
				self._raw_write(packet)

	def _raw_read(self, receiver, events, mux):
		return receiver.read(0xffff)

	def _raw_write(self, packet):
		self._sender.write(packet)

	def set_radio_lock(self, lock):
		self._radio_lock = lock
		self.logger.getChild('ctrl').debug("set_radio_lock: {}".format(self._radio_lock))

	def set_radio_baud(self, baud):
		if self._radio_lock:
			self.logger.getChild('ctrl').debug("set_radio_baud: Radio locked, ignoring")
			return
		self._program(self._sender, 'AT+B{:d}'.format(baud))
		self._baud = baud
		self.logger.getChild('ctrl').debug("set_radio_baud: {}".format(self._baud))

	def set_radio_channel(self, channel):
		if self._radio_lock:
			self.logger.getChild('ctrl').debug("set_radio_channel: Radio locked, ignoring")
			return
		self._program(self._sender, 'AT+C{:03d}'.format(channel))
		self._channel = channel
		self.logger.getChild('ctrl').debug("set_radio_channel: {}".format(self._channel))


def listify(x):
	if isinstance(x, list):
		return x
	return [x]


def main():
	import argparse
	ap = argparse.ArgumentParser()
	ap.add_argument("--config")
	ap.add_argument("--logconf", default=None)
	ap.add_argument("--verbose", "--debug", "-v", action='store_true')
	args = ap.parse_args()

	if args.logconf:
		logging.config.fileConfig(args.logconf, disable_existing_loggers=False)
	else:
		formatter = logging.Formatter("[{name}] {asctime} {levelname}: {message}", "%Y-%m-%dT%H:%M", '{')
		stderr_handler = logging.StreamHandler(sys.stderr)
		stderr_handler.setFormatter(formatter)
		logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)
		logging.getLogger().addHandler(stderr_handler)

	with open(args.config, 'r') as f:
		config = yaml.load(f)

	mux = Mux()

	for interface in config['interfaces']:
		if interface['type'] == 'serial':
			iface = InterfaceSerial(interface)
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

	logging.getLogger().debug("{:d} interfaces, {:d} routes".format(len(mux.interfaces), len(mux.routes)))
	mux.run()

if __name__ == '__main__':
	main()