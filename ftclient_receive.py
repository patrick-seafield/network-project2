#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - ftclient_receive.py

import socket
import sys
import string

def receiveListDirectory(opts):
    print('Receiving directory structure from {serverHost}:{dataPort}'.format(**opts))


def receiveFile(opts):
    print('Receiving “{filename}” from {serverHost}:{dataPort}'.format(**opts))
