#!/usr/bin/python3

import math
import struct

import serial
import selectors
import time

from series import Series
from soeren_series import *


class ProducerSerial:
	def __init__(self, ser):
		self.ser = ser
		self.handlers = {  # (length_without_checksum)
			b'M': (7, self.handle_magnetic),
			b'F': (13, self.handle_flight),
			b'P': (5, self.handle_power),
			b'T': (5, self.handle_atmosphere),
			b'G': (16, self.handle_gps),
			b'c': (6, self.handle_control),
			b'i': (1, self.handle_info),
		}
		self.buf = bytearray()
		self.debug = print

	def run(self):
		sel = selectors.DefaultSelector()
		sel.register(self.ser, selectors.EVENT_READ)
		while True:
			sel.select()
			self.update(int(time.time()*1000))

	def update(self, t):
		upd = self.ser.read(8192)
		#print(upd)
		self.buf.extend(upd)
		#print(self.buf)
		for packet in self.parse():
			hlen, handler = self.handlers.get(bytes(packet[0:1]), (None, None))
			if handler is not None:
				handler(t, packet[1:])

	def parse(self):
		while len(self.buf) > 0:
			plen, handler = self.handlers.get(bytes(self.buf[0:1]), (None, None))
			if plen is not None:
				if len(self.buf) < plen + 1:
					return
				packet = self.buf[:plen]
				cksum = self.buf[plen]
				#verify
				cs = 0
				for b in packet:
					cs ^= b
				if cksum == cs:
					self.buf = self.buf[plen+1:]
					yield packet
					continue
			self.buf = self.buf[1:]

	def handle_magnetic(self, t, packet):
		mx, my, mz = struct.unpack('!hhh', packet)
		DATA_MAGNETIC.append(t, mx, my, mz)
		self.debug(f'\033[1;31mmag ({mx}, {my}, {mz})\033[0m')

	def handle_flight(self, t, packet):
		gx, gy, gz, ax, ay, az = struct.unpack('!hhhhhh', packet)
		gx, gy, gz, ax, ay, az = gx/16.4, gy/16.4, gz/16.4, ax/2048, ay/2048, az/2048
		DATA_FLIGHT.append(t, gx, gy, gz, ax, ay, az)
		self.debug(f'\033[1;33mflg g=({gx:.2f}, {gy:.2f}, {gz:.2f}) a=({ax:.2f}, {ay:.2f}, {az:.2f})\033[0m')

	def handle_power(self, t, packet):
		i, u = struct.unpack('!hH', packet)
		u, i = u/1000, i/1000
		DATA_POWER.append(t, u, i)
		self.debug(f'\033[1;34mpwr u={u:.2f} i={i:.2f}\033[0m')

	def handle_atmosphere(self, t, packet):
		p, temp = struct.unpack('!Hh', packet)
		p, temp = p*10, temp/10
		DATA_ATMO.append(t, temp, p)
		self.debug(f'\033[1;35matm t={temp:.2f} p={p:.2f}\033[0m')

	def handle_gps(self, t, packet):
		lat, lon, alt, links, yaw, vel = struct.unpack("!ffHBHH", packet)
		# lon = lon * 180 / (1<<31)
		# lat = lat * 180 / (1<<31)
		yaw = yaw / 100
		s, c = math.sin(yaw), math.cos(yaw)
		vel = vel / 100
		vx, vy = vel*s, vel*c
		DATA_GPS.append(t, lon, lat, alt, yaw, vx, vy, links)
		self.debug(f'\033[1;32mgps ({lat:.2f}N, {lon:.2f}E, {alt:.2f})*{links} | {yaw:.2f}° v=({vx:.2f}, {vy:.2f})\033[0m')

	def handle_control(self, t, packet):
		c0, c1, c2, c3, c4 = struct.unpack('!BBBBB', packet)
		DATA_CONTROL.append(t, c0, c1, c2, c3, c4)
		self.debug(f'\033[1;36mctr ({c0:.2f}, {c1:.2f}, {c2:.2f}, {c3:.2f}, {c4:.2f})\033[0m')

	def handle_info(self, t, packet):
		self.debug('\033[1;36minfo\033[0m')

class ProducerRandom:
	def __init__(self):
		self._last_t = 0

	def update(self, t):
		import random
		if t < self._last_t + 1:
			return
		DATA_MAGNETIC.append(t, random.uniform(0,1), random.uniform(0,1), random.uniform(0,1))
		DATA_FLIGHT.append(t, random.uniform(-360, 360), random.uniform(-360, 360), random.uniform(-360, 360), random.uniform(-4,4), random.uniform(-4,4), random.uniform(-4,4))
		DATA_POWER.append(t, random.uniform(-1,12), random.uniform(-2,2))
		DATA_ATMO.append(t, random.uniform(-50,50), random.uniform(5000,10000))
		DATA_CONTROL.append(t, random.randint(0,180), random.randint(0,180), random.randint(0,180), random.randint(0,180), random.randint(0,180))
		v = random.uniform(0, 55)
		yaw = random.uniform(0,360)
		s, c = math.sin(yaw), math.cos(yaw)
		DATA_GPS.append(t, random.uniform(46, 50), random.uniform(8, 12), random.uniform(0, 1<<16), yaw, v*s, v*c, random.randint(1,3))
		self._last_t = t

	def run(self):
		while True:
			self.update(int(time.time() * 1000))
			time.sleep(1)


def main():
	import argparse
	ap = argparse.ArgumentParser("Receive/generate telemetry and store to disk")
	ap.add_argument("--serial", action='store', dest='ser', default=None)
	ap.add_argument("--baudrate", default=115200, type=int)
	args = ap.parse_args()

	if args.ser is None:
		producer = ProducerRandom()
	else:
		producer = ProducerSerial(serial.Serial(args.ser, args.baudrate, timeout=0))

	try:
		producer.run()
	except KeyboardInterrupt:
		DATA_MAGNETIC.close()
		DATA_FLIGHT.close()
		DATA_POWER.close()
		DATA_ATMO.close()
		DATA_CONTROL.close()
		DATA_GPS.close()

if __name__ == '__main__':
	main()