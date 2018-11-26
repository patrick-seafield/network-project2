#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient_receive.py

import socket
import sys
import string

BUFFER_SIZE = 1024

def receiveListDirectory(opts):
    print('Receiving directory structure from {serverHost}:{dataPort}'.format(**opts))

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((opts['serverHost'], opts['dataPort']))
        s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, BUFFER_SIZE)

        while True:
            data = s.recv(1024)
            if data is None or len(data) == 0:
                break
            else:
                print(data.decode())
            



def receiveFile(opts):
    print('Receiving “{filename}” from {serverHost}:{dataPort}'.format(**opts))

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((opts['serverHost'], opts['dataPort']))
        s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, BUFFER_SIZE)

        while True:
            data = s.recv(1024)
            if data is None or len(data) == 0:
                break
            else:
                print(data.decode())
