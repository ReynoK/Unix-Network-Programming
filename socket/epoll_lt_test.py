import select
import socket 
import os
import time
import multiprocessing

def server(address):
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serversocket.bind(address)
    serversocket.listen(1)
    serversocket.setblocking(0)

    poller = select.epoll()
    poller.register(serversocket.fileno(), select.EPOLLIN)

    while True:
        events = poller.poll()
        time.sleep(1)
        print("Server events:",events)
        

def client(address):
    time.sleep(1)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(address)
    print("Client start connect!")
    time.sleep(1000)


def main():
    address = ('0.0.0.0', 8080)
    server_process = multiprocessing.Process(target=server, args =(address,))
    client_process = multiprocessing.Process(target=client, args=(address, ))

    server_process.start()
    client_process.start()

    client_process.join()
    server_process.join()


if __name__ == "__main__":
    main()
