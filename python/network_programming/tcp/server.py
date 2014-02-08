import socket

server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.bind(("127.0.0.1", 8000))
server_sock.listen(1)
while 1:
    conn, addr = server_sock.accept()
    while 1:
        data = conn.recv(1024)
        if not data: break;
        conn.sendall(data)
    conn.close()
