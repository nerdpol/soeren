import argparse
import functools
import json
import logging
import logging.config
import sys

import curio
from curio import socket

logger = None

async def beat(sock, port, period, id, callsign, timestamps, timeout):
	global logger
	while True:
		now = await curio.clock()
		hear_ids = [id for id, last_heard in timestamps.items() if last_heard > now - timeout]
		hear = functools.reduce(lambda a, b: a | (1 << b), hear_ids, 0)
		message = {"_type": "heartbeat", "callsign": callsign, "id": id, "hear": hear}
		logger.getChild("out").info(message)
		packet = json.dumps(message).encode()
		await sock.sendto(packet, ('<broadcast>', port))
		await curio.sleep(period)


async def listen(sock, timestamps):
	global logger
	while True:
		packet, addr = await sock.recvfrom(0xffff)
		if addr == sock.getsockname():
			continue
		message = json.loads(packet.decode())
		if message['_type'] != 'heartbeat':
			continue
		logger.getChild("in").info(message)
		timestamps[message['id']] = await curio.clock()


async def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--bind", default="127.0.0.1")
	ap.add_argument("--port", type=int, default=7373)
	ap.add_argument("--period", type=float, default=3)
	ap.add_argument("--timeout", type=float, default=7)
	ap.add_argument("--logconf", default=None)
	ap.add_argument("--verbose", "--debug", "-v", action='store_true')
	ap.add_argument("id", type=int)
	ap.add_argument("callsign", type=str)
	args = ap.parse_args()

	if args.id < 0 or args.id > 7:
		raise ValueError("Invalid ID (must be 0-7)")
	if len(args.callsign.encode()) > 12:
		raise ValueError("Callsign too long (max 16 bytes UTF-8)")
	if args.period < 0.1:
		raise ValueError("Heartbeat period too short, refusing to saturate the ether")

	if args.logconf:
		logging.config.fileConfig(args.logconf, disable_existing_loggers=False)
	else:
		formatter = logging.Formatter("[{name}] {asctime} {levelname}: {message}", "%Y-%m-%dT%H:%M", '{')
		stderr_handler = logging.StreamHandler(sys.stderr)
		stderr_handler.setFormatter(formatter)
		logging.getLogger().setLevel(logging.DEBUG if args.verbose else logging.INFO)
		logging.getLogger().addHandler(stderr_handler)

	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)  
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1) 
	sock.bind((args.bind, args.port))

	global logger
	logger = logging.getLogger("heartbeat")

	timestamps = {}

	async with curio.TaskGroup() as tg:
		await tg.spawn(beat(sock, args.port, args.period, args.id, args.callsign, timestamps, args.timeout))
		await tg.spawn(listen(sock, timestamps))


if __name__ == '__main__':
	curio.run(main())
