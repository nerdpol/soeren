from socket import *
import json
import threading
import time

# map x in range in_min - in_max to the new range out_min - out_max 
def valueMap(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def progress_bar(x, x_min, x_max, width=30, pchar='#'):
    print("[ ", end='')
    converted = int(valueMap(x, x_min, x_max, 0, width))
    for i in range(converted):
        print(pchar, end='')
    for i in range(width-converted):
        print(" ", end='')
    print(f" ]  {x} / {x_max}")

messages = [
    {"_type": "accel", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "battery", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "gps", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "mag", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "power", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "quat", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "telemetry_radio", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "status", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "atmosphere", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "gyro", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "heartbeat", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "debug", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "control", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "lock", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "panic", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "control_radio", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "servos", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "telemetry", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "unlock", "accel0": 24, "accel1": 1337, "accel2": 42},
    {"_type": "switches", "accel0": 24, "accel1": 1337, "accel2": 42},
]

class UdpDummySender():
    def __init__(self):
        self.cs = socket(AF_INET, SOCK_DGRAM)
        self.cs.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        self.cs.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)

    def send_messages(self):
        """
        test out all paket types

        """
        global messages
        # send out
        for msg in messages:
            self.cs.sendto(json.dumps(msg).encode(encoding='ascii'), ('255.255.255.255', 5005))
            print("sending:", msg)

    def send_quat_data(self, freq = 60, skip = 0):
        """
        send real quaternion data
        read from file and send this repeatedly
        this is a blocking function
        """

        print('send_quat_data()')
        try:
            with open("../demo_data/quats.txt", "r") as quatsfile:
                self.quats = quatsfile.readlines()
                self.quats_dicts = [json.loads(quat) for quat in self.quats]
                self.quats_len = len(self.quats_dicts)
        except:
            print("Error reading example quaternion file")

        #
        cur_index = 0
        try:
            while 1:
                self.cs.sendto(json.dumps(self.quats_dicts[cur_index]).encode(encoding="ascii"), ('127.0.0.1', 5005))
                cur_index += skip + 1
                cur_index = cur_index % self.quats_len
                print()
                print('sending:', self.quats_dicts[cur_index])
                progress_bar(cur_index, 0, self.quats_len)
                time.sleep(1 / freq)
        except KeyboardInterrupt:
            exit(0)

if __name__ == '__main__':
    sender = UdpDummySender()
    sender.send_quat_data(freq = 15, skip = 3)