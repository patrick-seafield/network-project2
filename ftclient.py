#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient.py

import socket
import sys
import os
import string

from validateArgs import validate
from ftclient_receive import receiveListDirectory, receiveFile, BUFFER_SIZE


# main()
if __name__ == '__main__':
    # Check that the user has supplied valid arguments.
    opts = validate(sys.argv)
    if (opts is None):
        sys.exit(1)

    # Check if the file already exists locally.
    if opts['command'] == '-g' and os.path.isfile(opts['filename']):
        should_override = input("File already exists. Override? (y/N): ")
        if should_override != 'y' and should_override != 'Y':
            print("Exiting.")
            sys.exit(1)
        
    # Open the socket on the user-specified server.
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((opts['serverHost'], opts['serverPort']))
        s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, BUFFER_SIZE)

        # Ask for a list of downloadable files.
        if opts['command'] == '-l':
            command = "-l {dataPort}".format(**opts).encode('ascii')
            bytes_sent = s.send(command)
            
            data = s.recv(BUFFER_SIZE - 1).decode()
            if data is not None:
                response = data[:-1] # Strip the \0 character.
                if response == 'OK-l':
                    receiveListDirectory(opts)
                else:
                    print("{serverHost}:{serverPort} says: {response}".format(
                        response=response, **opts))
                    sys.exit(1)

        if opts['command'] == '-g':
            command = "-g {filename} {dataPort}".format(**opts).encode('ascii')
            bytes_sent = s.send(command)
            
            data = s.recv(BUFFER_SIZE - 1).decode()
            if data is not None:
                response = data[:-1] # Strip the \0 character.
                if response == 'OK-g':
                    receiveFile(opts)
                else:
                    print("{serverHost}:{serverPort} says: {response}".format(
                        response=response, **opts))
                    sys.exit(1)
