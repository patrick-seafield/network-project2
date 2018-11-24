#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient.py

import socket
import sys
from validateArgs import validate

# main()
if __name__ == '__main__':
    opts = validate(sys.argv)
    if (opts is None):
        sys.exit(1)
    
    if opts['command'] == '-l':
        print('Receiving directory structure from {serverHost}:{serverPort}'.format(**opts))
