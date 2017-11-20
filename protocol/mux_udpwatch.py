import argparse
import json
import socket


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", type=int, default=7373)
	args = ap.parse_args()

	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.bind(('127.0.0.1', args.port))

	while True:
		packet, _ = sock.recvfrom(4096)
		message = json.loads(packet.decode())
		print(message)


if __name__ == '__main__':
	main()
