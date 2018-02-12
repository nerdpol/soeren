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


class UdpDummySender():
    def __init__(self):
        self.cs = socket(AF_INET, SOCK_DGRAM)
        self.cs.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        self.cs.setsockopt(SOL_SOCKET, SO_BROADCAST, 1)
        self.load_gps_data()

    def send_object(self, obj):
        """
        test out all paket types

        """
        as_str = json.dumps(obj).encode(encoding='ascii')
        self.cs.sendto(as_str, ('255.255.255.255', 5005))
        print("sending:", as_str)

    def load_gps_data(self):
        with open('gps_data.json', 'r') as file:
            data = file.read()
            self.gps_data = json.loads(data)

    def send_gps_data(self, freq = 60):
        for payload in self.gps_data:
            self.send_object(payload)
            time.sleep(1 / freq)

if __name__ == '__main__':
    sender = UdpDummySender()
    while 1:
        sender.send_gps_data(freq = 60)
