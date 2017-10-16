import socket
import json
import queue

class UdpReceiver():


    def __init__(self, recv_port = 5005):
        self.recv_port = recv_port
        print("Initialize UdpReceiver at port", 5005)
        self.sock = socket.socket(socket.AF_INET, # Internet
                             socket.SOCK_DGRAM) # UDP
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', self.recv_port))

    def listen(self, q: queue.Queue):
        """

        queue: Queue, containing the last dict objects.
        """
        print("udpreceiver listening...")
        while 1:
            # max len
            data, addr = self.sock.recvfrom(0xffff)

            # parse json
            try:
                parsed_json = json.loads(data.decode())
                q.put(parsed_json, block=False)
                print(parsed_json)
            except json.JSONDecodeError:
                print("Could't parse json!")




def testListen():
    ur = UdpReceiver()
    q = queue.Queue()
    ur.listen(q)

if __name__ == '__main__':
    testListen()