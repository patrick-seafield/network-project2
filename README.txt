Patrick Seafield (seafielp@oregonstate.edu)
CS 372, 400, Fall 2018

Project 2: ftserver and ftclient

# EXTRA CREDIT
  - [X] Multithreaded server
  - [X] Transfer files other than text files
  - [ ] Allow client to change directory (?? specify for listing)
  - [ ] Username/Password authentication
    - [ ] Require username/password
    - [ ] Allow anonymous users


# ftserver

To make ftserver, simply run make.

flip-shell$ make

The ftserver executable will be created in the local directory.

EXTRA CREDIT!

- ftserver can handle 8 incoming connections concurrently. It calls
    fork() to launch a child process and handle the connection.

- ftserver serves files as binary files, so non-text files can be
    transferred.





# ftclient

I wrote ftclient in python. To run it, simply run ftclient.py

flip-shell$ ./ftclient.py

If you request a file, and it already exists locally, you will be
prompted to override it (or not).

