import math
import time

import joystick

def sinoid(period, min, max, t):
	v = 0.5 * (math.sin(2*math.pi/period*t) + 1)
	return min + v * (max - min)

def main(tty, baudrate, period, update_interval):
	serial_interface = joystick.init_serial(tty, baudrate)

	try:
		t = 0
		while True:
			v = sinoid(period, 30, 155, t)
			joystick.send_joystick(serial_interface, v, 90, 90, 90)
			t += update_interval
			time.sleep(update_interval)
	except KeyboardInterrupt:
		joystick.send_joystick(serial_interface, 90, 90, 90, 90)

if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser(description='Joystick')
	parser.add_argument('tty', help="serial port name")
	parser.add_argument("--baudrate", "-b", type=int, default=115200, help="baud rate (default %(default)s)")
	parser.add_argument("--period", "-p", type=int, default=5, help="Sinoid period in seconds (default %(default)s)")
	parser.add_argument("--interval", "-i", type=float, default=0.1, help="packet interval in seconds (default %(default)s)")
	args = parser.parse_args()
	main(args.tty, args.baudrate, args.period, args.interval)
