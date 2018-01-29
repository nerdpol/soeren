import socket
import json
import queue
import time

def get_logger(tag):
    """
    get a log function with your logtag
    """
    def l(*msg):
        """ """
        print(tag, *msg)
    return l

def epoch_ms():
    millis = int(round(time.time() * 1000))
    return millis

DEBUG = True
log = get_logger("[UdpReceiver]")


class _UdpReceiver():
    """ """
    def __init__(self, recv_port):
        self.handlers = list()
        self.recv_port = recv_port
        if DEBUG: 
            log("Initialize UdpReceiver at port", recv_port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', self.recv_port))
        if DEBUG:
            log(f"listening for broadcast messages on port {recv_port}")

    def _receive(self):
        """
        Get one data packet via udp.
        :return: (data: dict, ok: bool)
        """
        data, _ = self.sock.recvfrom(0xffff)

        try:
            # try parsing
            parsed = json.loads(data.decode())
            _type = parsed["_type"]

            # add timestamp
            parsed.update({"timestamp": epoch_ms()})

            # return that
            return parsed, True

        except json.JSONDecodeError:
            log("Could't parse json!")
        except KeyError:
            log("Invalid packet!")
        return dict(), False


class UdpReceiverQueues(_UdpReceiver):
    """
    A Class to receive udp messages in a queue
    Intended Usage:

    # First, get an Instance and one or queues 
    >>> urq = UdpReceiverQueues()
    >>> my_queue = urq.get_queue("quat")  # I want all packets with the type "quat"

    # Then start the UdpReceiver in a separate thread
    >>> import threading
    >>> t = threading.Thread(None, urq.listen)
    >>> t.start()

    # in your program, query a value at some point (do this frequently)
    >>> a_packet = my_queue.get_nowait()
    >>> print(a_packet)

    """
    def __init__(self, recv_port=5005, max_queue_size=10):
        super().__init__(recv_port)

        self.max_queue_size = max_queue_size

        # key: type, value: queue
        self.queues = dict()

    def get_queue(self, recv_type):
        """
        get the queue for a given packet type.
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
        It's going to listen for incoming udp packets
        and push them into self.queues["packet_type"]
        ONLY if you previously called get_queue for a given packet type, e.g. "quat"
        """
        if DEBUG:
            log("listening...")
        while 1:
            parsed, ok = self._receive()
            if ok:
                _type = parsed["_type"]
                # check for queue being present
                if _type in self.queues:
                    self.queues[_type].put(parsed)
                    if DEBUG:
                        log(f"add to queue _type={_type}, isfull={self.queues[_type].full()}")
                

class UdpReceiverCallbacks(_UdpReceiver):
    """
    A Class to receive udp messages as callbacks
    Intended Usage:

    # First, get an Instance and one or queues 
    >>> urq = UdpReceiverCallbacks()
    >>> urq.register_listener("quat", lambda packet: print(packet))  # use packets here
    >>> urq.listen()
    """
    def __init__(self, recv_port=5005):
        super().__init__(recv_port)
        self.handlers = dict()
    
    def listen(self):
        """
        start this in a separate thread.
        It's going to listen for incoming udp packets
        and push them into self.queues["packet_type"]
        ONLY if you previously called get_queue for a given packet type, e.g. "quat"
        """
        if DEBUG:
            log("listening...")
        while 1:
            parsed, ok = self._receive()
            
            if ok:
                _type = parsed["_type"]

                # add timestamp
                parsed.update({"timestamp": epoch_ms()})

                # publish to all handlers 
                for _, handler in self.handlers.items():
                    handler(parsed)

    def register_listener(self, _type, handler):
        self.handlers[_type] = handler


def testListenQueues():
    ur = UdpReceiverQueues()
    q = ur.get_queue("quat")
    ur.listen()

def testListenHandler():
    ur = UdpReceiverCallbacks()
    ur.register_listener("quat", lambda parsed: print("success: ", parsed))
    ur.listen()

if __name__ == '__main__':
    # import doctest
    # doctest.testmod()
    # testListenQueues()
    testListenHandler()
