#!/usr/bin/env python3

import socket
import sys

#if (len(sys.argv) < 2):
#    print('Usage: Client <server-IP> <message>')
#    quit()

HOST = '127.0.0.1' # The server's hostname or IP address
PORT = 12345        # The port used by the server
bytes = "ola"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket_client:
    socket_client.connect((HOST, PORT))
    socket_client.sendall(str.encode(bytes))
