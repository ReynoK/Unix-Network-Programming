import socket
import os
import time

server_address = "/Users/reynokang/Temp/socket.sock"

if not os.path.exists(server_address):
    raise Exception("The sock file is not exist")

print("Connect to socket:", server_address)
client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
try:
    client_socket.connect(server_address)
except Exception as e:
    print(e)
    raise


def send_test(client_socket, send_data):
    time.sleep(1)
    print("Send:", send_data)
    client_socket.send(send_data)
    time.sleep(1)
    recv_data = client_socket.recv(1024)
    print("Echo:", recv_data)


print("Start communication!")
send_data = b"Hello, world!"
send_test(client_socket, send_data)
send_data = b"My name is Tom!"
send_test(client_socket, send_data)
print("Close connection!")
client_socket.close()
