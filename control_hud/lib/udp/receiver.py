import socket
import json
import queue
import time

def get_logger(tag):
    def l(*msg):
        print(tag, *msg)
    return l

def epoch_ms():
    millis = int(round(time.time() * 1000))
    return millis

DEBUG = True
log = get_logger("[UdpReceiver]")

class UdpReceiver():
    def __init__(self, recv_port):
        self.handlers = list()
        self.recv_port = recv_port
        log("Initialize UdpReceiver at port", recv_port)
        self.sock = socket.socket(socket.AF_INET, # Internet
                             socket.SOCK_DGRAM) # UDP
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', self.recv_port))
        if DEBUG:
            log(f"listening for broadcast messages on port {recv_port}")

    def listen(self, q: queue.Queue):
        """

        queue: Queue, containing the last dict objects.
        """
        if DEBUG:
            log("listening...")
        while 1:
            # max len
            data, addr = self.sock.recvfrom(0xffff)

            # parse json
            try:
                parsed_json = json.loads(data.decode())
                q.put(parsed_json, block=False)
                for handler in self.handlers:
                    handler(parsed_json)
                log(parsed_json)
            except json.JSONDecodeError:
                log("Could't parse json!")

    def register_listener(self, desired_type, handler):
        self.handlers.append(handler)


class UdpReceiverQueues(UdpReceiver):
    def __init__(self, recv_port = 5005, max_queue_size = 1000):
        super().__init__(recv_port)

        self.max_queue_size = max_queue_size

        # key: type, value: queue
        self.queues = dict()

    def get_queue(self, recv_type):
        """
        get the queue for a given paket type.
        you can now poll from the queue.
        Always call this before calling listen! 
        """
        # check if this queue is already there
        if recv_type not in self.queues:
            self.queues[recv_type] = queue.Queue(self.max_queue_size)
            if DEBUG:
                log(f"get_queue(): Queue for _type={recv_type} added")
        return self.queues[recv_type]

    def listen(self):
        """
        start this in a separate thread.
        It's going to listen for incoming udp pakets
        and push them into self.queues["packet_type"]
        ONLY if you previously called get_queue for a given paket type, e.g. "quat"
        """
        if DEBUG:
            log("listening...")
        while 1:

            data, _ = self.sock.recvfrom(0xffff)

            try:
                # try parsing
                parsed = json.loads(data.decode())
                _type = parsed["_type"]

                # add timestamp
                parsed.update({"timestamp": epoch_ms()})

                # check for queue being present
                if _type in self.queues:
                    self.queues[_type].put(parsed)
                    if DEBUG:
                        log(f"add to queue _type={_type}, qsize={self.queues[_type].qsize()}")
                

            except json.JSONDecodeError:
                log("Could't parse json!")
            except KeyError:
                log("Invalid paket!")


def testListen():
    ur = UdpReceiverQueues()
    q = ur.get_queue("quat")
    ur.listen()

if __name__ == '__main__':
    testListen()