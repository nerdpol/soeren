import serial
import sys
import time
import itertools



def main():
	import argparse
	ap = argparse.ArgumentParser()
	ap.add_argument('--length', default=10, type=int)
	ap.add_argument('--baud', default=115200, type=int)
	ap.add_argument('--interval', default=0.01, type=float)
	ap.add_argument('--read', dest='mode', const='read', action='store_const')
	ap.add_argument('--write', dest='mode', const='write', action='store_const')
	ap.add_argument('--alphabet', default='ABCDEFGHIJKLMNOPQRSTUVWXYZ')
	ap.add_argument('serial')
	args = ap.parse_args()

	it = itertools.cycle(args.alphabet.encode('ascii'))
	def mkpkg(n):
		return bytes(itertools.islice(it, 0, n))

	s = serial.Serial(args.serial, baudrate=args.baud)
	if args.mode == 'read':
		while True:
			print(s.read())
			time.sleep(args.interval)
	elif args.mode == 'write':
		while True:
			s.write(mkpkg(args.length))
			time.sleep(args.interval)
	else:
		raise RuntimeError("Invalid mode")

if __name__ == '__main__':
	main()
