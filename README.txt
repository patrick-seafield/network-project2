Patrick Seafield (seafielp@oregonstate.edu)
CS 372, 400, Fall 2018

Project 2: ftserver and ftclient


# ftserver

To make ftserver, simply run make.

flip-shell$ make

The ftserver executable will be created in the local directory.

EXTRA CREDIT:
- ftserver can handle 8 incoming connections concurrently.
  It calls fork() to launch a child process and handle the connection.




# ftclient
