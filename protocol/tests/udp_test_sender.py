import argparse
import json
import socket
from time import sleep


TEST_DATA = [

{
    "_type": "accel", "accel0": 90, "accel1": 10, "accel2": 0.1
},
{
    "_type": "quat", "quat0": 1, "quat1": 0, "quat2": 0, "quat3": 0
}

]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port", type=int, default=7373)
    args = ap.parse_args()

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    max_i = len(TEST_DATA)
    i = 0

    while 1:
        print("Send:", TEST_DATA[i])
        sock.sendto(json.dumps(TEST_DATA[i]).encode('ascii'), ("127.0.0.1", args.port))
        i += 1
        i %= max_i
        sleep(0.5)


if __name__ == '__main__':
    main()

