#!/usr/bin/python3

import argparse
import socket
import protocol


def command_control(pargs, cargs, sock):
	raise NotImplementedError()

def command_lock(pargs, cargs, sock):
	raise NotImplementedError()

def command_panic(pargs, cargs, sock):
	raise NotImplementedError()

def command_control_radio(pargs, cargs, sock):
	raise NotImplementedError()

def command_servos(pargs, cargs, sock):
	ap = argparse.ArgumentParser()
	ap.add_argument("servo0", type=int)
	ap.add_argument("servo1", type=int)
	ap.add_argument("servo2", type=int)
	ap.add_argument("servo3", type=int)
	ap.add_argument("servo4", type=int)
	ap.add_argument("servo5", type=int)
	ap.add_argument("servo6", type=int)
	ap.add_argument("servo7", type=int)
	cargs = ap.parse_args(cargs)

	message = {
		"_type": "servos",
		"servos0": cargs.servo0,
		"servos1": cargs.servo1,
		"servos2": cargs.servo2,
		"servos3": cargs.servo3,
		"servos4": cargs.servo4,
		"servos5": cargs.servo5,
		"servos6": cargs.servo6,
		"servos7": cargs.servo7,
	}
	packet = protocol.radio_packet_pack(message)
	sock.sendto(packet, ('255.255.255.255', pargs.port))

def command_telemetry(pargs, cargs, sock):
	raise NotImplementedError()

def command_unlock(pargs, cargs, sock):
	raise NotImplementedError()

def command_switches(pargs, cargs, sock):
	ap = argparse.ArgumentParser()
	ap.add_argument("action", choices=["set", "clr", "clear"])
	ap.add_argument("pin", type=int)
	ap.add_argument("value", nargs='?', type=int, default=1)
	cargs = ap.parse_args(cargs)

	cargs.value = int(bool(cargs.value))
	if cargs.pin < 0 or cargs.pin >= 8:
		raise ValueError()
	mask = 1 << cargs.pin
	value = cargs.value << cargs.pin
	if cargs.action != 'set':
		value = 0

	print(f"mask={mask:x}, value={value:x}")

	message = {
		"_type": "switches",
		"change_mask": mask,
		"change_value": value,
	}
	packet = protocol.radio_packet_pack(message)
	sock.sendto(packet, ('255.255.255.255', pargs.port))

def command_mux_radio_lock(pargs, cargs, sock):
	raise NotImplementedError #{"_type": "_mux_radio_lock", "lock": <>}

def command_mux_radio_baud(pargs, cargs, sock):
	raise NotImplementedError #{"_type": "_mux_radio_baud", "baud": <>}

def command_mux_radio_channel(pargs, cargs, sock):
	raise NotImplementedError #{"_type": "_mux_radio_channel", "channel": <>}

def main():
	ap = argparse.ArgumentParser()
	ap.add_argument("--port", type=int, default=7373)
	ap.add_argument("command", choices=[name.replace("command_", "", 1) for name in globals() if name.startswith("command")])
	ap.add_argument("args", nargs=argparse.REMAINDER)
	args = ap.parse_args()

	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.bind(('127.0.0.1', args.port))

	return globals()["command_"+args.command](args, args.args, sock)


if __name__ == '__main__':
	main()
