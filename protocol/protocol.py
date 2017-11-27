# THIS FILE IS GENERATED, DO NOT EDIT BY HAND

import struct

def radio_packet_size(id):
	return {
		b'A': 6,
		b'B': 4,
		b'G': 15,
		b'M': 6,
		b'P': 4,
		b'Q': 16,
		b'R': 0,
		b'S': 0,
		b'T': 4,
		b'Y': 6,
		b'H': 14,
		b'D': 16,
		b'c': 0,
		b'l': 4,
		b'p': 1,
		b'r': 0,
		b's': 8,
		b't': 12,
		b'u': 4,
		b'w': 2,
	}.get(id, None)

def radio_packet_parse(packet):
	if packet[0:1] == b"A":
		_type,accel0,accel1,accel2, = struct.unpack('!c3h', packet)
		return {"_type": "accel", "accel0": accel0, "accel1": accel1, "accel2": accel2}
	if packet[0:1] == b"B":
		_type,t_inside,t_outside, = struct.unpack('!chh', packet)
		return {"_type": "battery", "t_inside": t_inside, "t_outside": t_outside}
	if packet[0:1] == b"G":
		_type,latitude,longitude,altitude,links,yaw,velocity, = struct.unpack('!cLLHBHH', packet)
		return {"_type": "gps", "latitude": latitude, "longitude": longitude, "altitude": altitude, "links": links, "yaw": yaw, "velocity": velocity}
	if packet[0:1] == b"M":
		_type,mag0,mag1,mag2, = struct.unpack('!c3h', packet)
		return {"_type": "mag", "mag0": mag0, "mag1": mag1, "mag2": mag2}
	if packet[0:1] == b"P":
		_type,voltage,current, = struct.unpack('!cHh', packet)
		return {"_type": "power", "voltage": voltage, "current": current}
	if packet[0:1] == b"Q":
		_type,quat0,quat1,quat2,quat3, = struct.unpack('!c4f', packet)
		return {"_type": "quat", "quat0": quat0, "quat1": quat1, "quat2": quat2, "quat3": quat3}
	if packet[0:1] == b"R":
		_type, = struct.unpack('!c', packet)
		return {"_type": "telemetry_radio"}
	if packet[0:1] == b"S":
		_type, = struct.unpack('!c', packet)
		return {"_type": "status"}
	if packet[0:1] == b"T":
		_type,temperature,pressure, = struct.unpack('!chH', packet)
		return {"_type": "atmosphere", "temperature": temperature, "pressure": pressure}
	if packet[0:1] == b"Y":
		_type,gyro0,gyro1,gyro2, = struct.unpack('!c3h', packet)
		return {"_type": "gyro", "gyro0": gyro0, "gyro1": gyro1, "gyro2": gyro2}
	if packet[0:1] == b"H":
		_type,callsign,id,hear, = struct.unpack('!c12sBB', packet)
		return {"_type": "heartbeat", "callsign": callsign.decode(), "id": id, "hear": hear}
	if packet[0:1] == b"D":
		_type,message, = struct.unpack('!c16s', packet)
		return {"_type": "debug", "message": message.decode()}
	if packet[0:1] == b"c":
		_type, = struct.unpack('!c', packet)
		return {"_type": "control"}
	if packet[0:1] == b"l":
		_type,lock, = struct.unpack('!cL', packet)
		return {"_type": "lock", "lock": lock}
	if packet[0:1] == b"p":
		_type,payload_ignored, = struct.unpack('!cB', packet)
		return {"_type": "panic", "payload_ignored": payload_ignored}
	if packet[0:1] == b"r":
		_type, = struct.unpack('!c', packet)
		return {"_type": "control_radio"}
	if packet[0:1] == b"s":
		_type,servos0,servos1,servos2,servos3,servos4,servos5,servos6,servos7, = struct.unpack('!c8B', packet)
		return {"_type": "servos", "servos0": servos0, "servos1": servos1, "servos2": servos2, "servos3": servos3, "servos4": servos4, "servos5": servos5, "servos6": servos6, "servos7": servos7}
	if packet[0:1] == b"t":
		_type,next,always,never, = struct.unpack('!cLLL', packet)
		return {"_type": "telemetry", "next": next, "always": always, "never": never}
	if packet[0:1] == b"u":
		_type,unlock, = struct.unpack('!cL', packet)
		return {"_type": "unlock", "unlock": unlock}
	if packet[0:1] == b"w":
		_type,change_mask,change_value, = struct.unpack('!cBB', packet)
		return {"_type": "switches", "change_mask": change_mask, "change_value": change_value}

def radio_packet_pack(message):
	if message["_type"] == "accel":
		return struct.pack('!c3h', b"A", message['accel0'], message['accel1'], message['accel2'])
	if message["_type"] == "battery":
		return struct.pack('!chh', b"B", message['t_inside'], message['t_outside'])
	if message["_type"] == "gps":
		return struct.pack('!cLLHBHH', b"G", message['latitude'], message['longitude'], message['altitude'], message['links'], message['yaw'], message['velocity'])
	if message["_type"] == "mag":
		return struct.pack('!c3h', b"M", message['mag0'], message['mag1'], message['mag2'])
	if message["_type"] == "power":
		return struct.pack('!cHh', b"P", message['voltage'], message['current'])
	if message["_type"] == "quat":
		return struct.pack('!c4f', b"Q", message['quat0'], message['quat1'], message['quat2'], message['quat3'])
	if message["_type"] == "telemetry_radio":
		return struct.pack('!c', b"R")
	if message["_type"] == "status":
		return struct.pack('!c', b"S")
	if message["_type"] == "atmosphere":
		return struct.pack('!chH', b"T", message['temperature'], message['pressure'])
	if message["_type"] == "gyro":
		return struct.pack('!c3h', b"Y", message['gyro0'], message['gyro1'], message['gyro2'])
	if message["_type"] == "heartbeat":
		return struct.pack('!c12sBB', b"H", message['callsign'].encode(), message['id'], message['hear'])
	if message["_type"] == "debug":
		return struct.pack('!c16s', b"D", message['message'].encode())
	if message["_type"] == "control":
		return struct.pack('!c', b"c")
	if message["_type"] == "lock":
		return struct.pack('!cL', b"l", message['lock'])
	if message["_type"] == "panic":
		return struct.pack('!cB', b"p", message['payload_ignored'])
	if message["_type"] == "control_radio":
		return struct.pack('!c', b"r")
	if message["_type"] == "servos":
		return struct.pack('!c8B', b"s", message['servos0'], message['servos1'], message['servos2'], message['servos3'], message['servos4'], message['servos5'], message['servos6'], message['servos7'])
	if message["_type"] == "telemetry":
		return struct.pack('!cLLL', b"t", message['next'], message['always'], message['never'])
	if message["_type"] == "unlock":
		return struct.pack('!cL', b"u", message['unlock'])
	if message["_type"] == "switches":
		return struct.pack('!cBB', b"w", message['change_mask'], message['change_value'])
	else:
		raise ValueError("Unknown packet type")

