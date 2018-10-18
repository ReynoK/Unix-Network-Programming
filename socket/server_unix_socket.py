import socket
import os

server_address = "/Users/reynokang/Temp/socket.sock"

if os.path.exists(server_address):
    raise Exception("The sock file is exist")



server_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server_socket.bind(server_address)
server_socket.listen(1)

try:
    while True:
        print("Start accept!")

        client_socket,client_address = server_socket.accept()
        
        while True:
            print("Connect from:", client_address)

            data = client_socket.recv(1024)
            if not data:
                print("Connection closed by client!\n")
                break
            else:
                print("Received:", data)
                print("Send back:", client_socket.sendall(data))

    os.unlink(server_address)
except Exception as e:
    print(e)
    if os.path.exists(server_address):
        os.unlink(server_address)
