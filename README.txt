Patrick Seafield (seafielp@oregonstate.edu)
CS 372, 400, Fall 2018

Project 2: ftserver and ftclient

# EXTRA CREDIT
  - [X] Multithreaded server
  - [ ] Transfer files other than text files
  - [ ] Allow client to change directory (?? specify for listing)
  - [ ] Username/Password authentication
    - [ ] Require username/password
    - [ ] Allow anonymous users


# ftserver

To make ftserver, simply run make.

flip-shell$ make

The ftserver executable will be created in the local directory.

EXTRA CREDIT:
- ftserver can handle 8 incoming connections concurrently.
  It calls fork() to launch a child process and handle the connection.




# ftclient


