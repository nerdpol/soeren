import argparse
import time
import binascii
import struct
from functools import reduce
from math import exp

import serial
import pygame

def init_joystick():
	pygame.init()
	pygame.joystick.init()
	joystick = pygame.joystick.Joystick(0)
	joystick.init()
	return joystick

def init_serial(tty, baudrate):
	ser = serial.Serial(port=tty, baudrate=baudrate)
	if not ser.isOpen():
		ser.open()
	return ser

def unlinear(value, factor=2):
	is_negative = value < 0
	if is_negative:
		value = -value
	n = (exp(value * factor) - 1) / (exp(factor) - 1)
	if is_negative:
		n = -n
	return n

def calculate_servo_positions(x, y, z, s):
	# x = roll y= pitch z= yaw s = speed
	# Y = (X-A)/(B-A) * (D-C) + C
	# joystick out: A = -1 B = 1 (from -1 to 1) servo in: C = 0 D = 180 (from 0 to 180)

	x1 = -x + y
	y1 = -x - y
	s = -s

	if x1 > 1:
		x1 = 1
	if x1 < -1:
		x1 = -1
	if y1 > 1:
		y1 = 1
	if y1 < -1:
		y1 = -1

	return [(unlinear(i) - -1) / (1 - -1) * (155 - 25) + 25 for i in (x1, y1, z, s)]

def send_packet(serial_interface, packet):
	checksum = struct.pack("!B", reduce(int.__xor__, packet))
	serial_interface.write(packet + checksum)

last_servo = None
def send_joystick(serial_interface, x, y, z, s):
	global last_servo
	if last_servo != (x, y, z, s):
		last_servo = (x, y, z, s)
		print("Servo x={}, y={}, z={}, s={}".format(*last_servo))
		command = struct.pack("!cBBBBB", b'c', int(x), int(y), int(z), int(s), 90)
		send_packet(serial_interface, command)

def send_info(serial_interface):
	print("Info")
	send_packet(serial_interface, b'i')

def main(tty, baudrate, update_interval):
	joystick = init_joystick()
	serial_interface = init_serial(tty, baudrate)
	print("Using: ", joystick.get_name())

	while True:
		for event in pygame.event.get():
			if event.type == pygame.JOYAXISMOTION:
				positions = calculate_servo_positions(joystick.get_axis(0), joystick.get_axis(1), joystick.get_axis(2), joystick.get_axis(3))
				send_joystick(serial_interface, *positions)
			elif event.type == pygame.JOYBUTTONUP:
				send_info(serial_interface)

		time.sleep(update_interval)

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Joystick')
	parser.add_argument('tty', help="serial port name")
	parser.add_argument("--baudrate", "-b", type=int, nargs='?', help='set baud rate, default: %(default)s', default=115200)
	parser.add_argument("--interval", "-i", type=float, nargs='?', help='Set update interval, default: %(default)s', default=0.1)
	args = parser.parse_args()
	main(args.tty, args.baudrate, args.interval)
