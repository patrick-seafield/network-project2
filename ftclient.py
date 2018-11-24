#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient.py

import socket
import sys
from validateArgs import validate


BUFFER_SIZE = 2048

# main()
if __name__ == '__main__':
    # Check that the user has supplied valid arguments.
    opts = validate(sys.argv)
    if (opts is None):
        sys.exit(1)

    # Open the socket on the user-specified server.
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

        # Ask for a list of downloadable files.
        if opts['command'] == '-l':
            print('Receiving directory structure from {serverHost}:{serverPort}'.format(**opts))
            s.connect((opts['serverHost'], opts['serverPort']))
            # s.sendall(b'-l')

            data = s.recv(BUFFER_SIZE)
            if data is not None:
                print(repr(data))
