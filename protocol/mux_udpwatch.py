import argparse
import json
import socket


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--bind", default="127.0.0.1")
	ap.add_argument("--port", type=int, default=7373)
	args = ap.parse_args()

	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1) 
	sock.bind(('', args.port))

	while True:
		packet, _ = sock.recvfrom(4096)
		message = json.loads(packet.decode())
		print(message)


if __name__ == '__main__':
	main()
