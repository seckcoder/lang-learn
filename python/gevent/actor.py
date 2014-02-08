import gevent
from gevent.queue import Queue

class Actor(gevent.Greenlet):

    def __init__(self):
        self.inbox = Queue()
        super(Actor, self).__init__()
        #Greenlet.__init__(self)
    def receive(self, message):
        """
        Define in your subclass.
        """
        raise NotImplemented()

    def _run(self):
        self.running = True

        while self.running:
            message = self.inbox.get()
            self.receive(message)

class PingPongActor(Actor):
    def get_response(self):
        return self.response
    def set_responser(self, response):
        self.response = response
    responser = property(get_response, set_responser)

class Pinger(PingPongActor):
    def receive(self, message):
        print message
        gevent.sleep(2)
        self.responser.inbox.put('ping')

class Ponger(PingPongActor):
    def receive(self, message):
        print message
        gevent.sleep(2)
        self.responser.inbox.put('pong')

ping = Pinger()
pong = Ponger()
ping.responser = pong
pong.responser = ping

ping.start()
pong.start()

ping.inbox.put('start')
gevent.sleep(10)
#gevent.joinall([ping, pong])
