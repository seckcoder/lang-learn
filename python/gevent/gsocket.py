from gevent import socket

address = ('localhost', 9000)
message = "haha"
sock = socket.socket(type=socket.SOCK_DGRAM)
sock.connect(address)
print "sending %s bytes to %s:%s" % ((len(message), ) + address)
sock.send(message)
data, address = sock.recvfrom(8192)
print "%s:%s: got %r" % (address + (data, ))
