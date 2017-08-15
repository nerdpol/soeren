import math
import time

import joystick

def main(tty, baudrate, update_interval):
	serial_interface = joystick.init_serial(tty, baudrate)

	try:
		t = 0
		while True:
			joystick.send_joystick(serial_interface, 30 + (155-30)*(0.5*(math.sin(t)+1)), 90, 90, 90)
			t += update_interval
			time.sleep(update_interval)
	except KeyboardInterrupt:
		joystick.send_joystick(serial_interface, 90, 90, 90, 90)

if __name__ == '__main__':
	import argparse
	parser = argparse.ArgumentParser(description='Joystick')
	parser.add_argument('tty', help="serial port name")
	parser.add_argument("--baudrate", "-b", type=int, nargs='?', help='set baud rate, default: %(default)s', default=115200)
	parser.add_argument("--interval", "-i", type=float, nargs='?', help='Set update interval, default: %(default)s', default=0.1)
	args = parser.parse_args()
	main(args.tty, args.baudrate, args.interval)
