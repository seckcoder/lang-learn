from gevent.server import DatagramServer
class EchoServer(DatagramServer):
    def handle(self, data, address):
        print '%s: got %r' % (address[0], data)
        self.socket.sendto('Received %s bytes' % len(data), address)

EchoServer(':9000').serve_forever()
