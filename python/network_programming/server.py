#!/usr/bin/env python
import socket
import os
import threading
def echo_server_simple():
    host = ''
    port = 30000
    backlog = 5
    size = 1024
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((host, port))
    s.listen(backlog)
    while 1:
        client, address = s.accept()
        data = client.recv(size)
        if data:
            client.send(data)
        client.close()

echo_server_simple()
