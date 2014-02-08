#!/usr/bin/env python
import socket
def echo_client_simple():
    host = ''
    port = 10000
    size = 1024
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.send('Hello world')
    data = s.recv(size)
    s.close()
    print 'Received:', data
echo_client_simple()

