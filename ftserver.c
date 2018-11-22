#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "constants.h"
#include "ftserver_bind.h"


int main(int argc, char **argv)
{
  // Check that we have enough arguments for a port, and that we can bind to the port.
  if (argc < 2)
  {
    printf("USAGE %s PORT\n", argv[0]);
    exit(1);
  }

  // Bind to the user-specified port on this server.
  int sockfd = ftserver_bind(argv[1]);

  // Listen for incoming connections on our socket.
  if (listen(sockfd, CONNECTION_COUNT) == -1)
  {
		perror("listen() failed");
		exit(1);
	}

  // Ignore SIGCHLD so we can continue to serve multiple connections.
  struct sigaction sa;
  sa.sa_handler = wait_children;
  sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
  {
		perror("SIGCHLD handler setup failed");
		exit(1);
	}

  // Our main loop.
  // Wait for connections and respond appropriately.
  int acceptfd;
  struct sockaddr_storage client_addr;
  socklen_t addr_size;

  while (1)
  {
    // Accept a new incoming connection.
    addr_size = sizeof client_addr;
    acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
    if (acceptfd == -1)
    {
      perror("accept() failed");
      exit(1);
    }

    // Fork a child process to communicate with the client.
    if (!fork())
    {
      // Child process.
      close(sockfd);

      // Say hello.
      if (list_directory(acceptfd) == -1)
      {
        perror("send() failed");
      }

      // Close remaining file descriptor and exit.
      close(acceptfd);
      exit(0);
    }
    else
    {
      // Only the child process needs this.
      close(acceptfd);
    }
  }
}
