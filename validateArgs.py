#!/usr/bin/env python3
# Patrick Seafield (seafielp)
# CS 372 / 400 / F2018
# Project 2 - validateArgs.py

def printUsage():
    print("USAGE:\n\tftclient.py SERVER_HOST, SERVER_PORT, COMMAND, DATA_PORT")
    print("COMMANDS:")
    print("\t-l\t\tList the files on the server.")
    print("\t-g FILENAME\tDownload the file from the server.")


# Check that the arguments supplied by the user are valid.
def validate(args):
    opts = {}
    if len(args) < 5:
        printUsage()
        return None
    
    opts['serverHost'] = args[1]
    opts['command'] = args[3]

    try:
        opts['serverPort'] = int(args[2])
    except ValueError:
        printUsage()
        print("\nServer Port must be an integer.")
        return None

    if opts['command'] == "-l":
        try:
            opts['dataPort'] = int(args[4])
        except ValueError:
            printUsage()
            print("\nData Port must be an integer.")
            return None
            
    elif opts['command'] == "-g":
        if len(args) < 6:
            printUsage()
            sys.exit(1)
        else:
            opts['filename'] = args[4]
            try:
                opts['dataPort'] = int(args[5])
            except ValueError:
                printUsage()
                print("\nData Port must be an integer.")
                return None

    return opts

