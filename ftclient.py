#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient.py

import socket
import sys
import string

from validateArgs import validate
from ftclient_receive import receiveListDirectory, receiveFile

BUFFER_SIZE = 1024


# main()
if __name__ == '__main__':
    # Check that the user has supplied valid arguments.
    opts = validate(sys.argv)
    if (opts is None):
        sys.exit(1)

    # Open the socket on the user-specified server.
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((opts['serverHost'], opts['serverPort']))
        s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, BUFFER_SIZE)

        # Ask for a list of downloadable files.
        if opts['command'] == '-l':
            command = "-l {dataPort}".format(**opts).encode('ascii')
            print("Sending command:", command)
            bytes_sent = s.send(command)
            
            data = s.recv(BUFFER_SIZE - 1).decode()
            if data is not None:
                response = data[:-1] # Strip the \0 character.
                print(response)
                if response == 'OK-l':
                    receiveListDirectory(opts)
                else:
                    print("Problem with server response to command. Exiting.")
                    sys.exit(1)
