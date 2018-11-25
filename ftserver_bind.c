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

int ftserver_bind(char * port)
{
  int sockfd, status;
  int y = 1;
  struct addrinfo hints, *servinfo, *p;

  memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

  // Get the server hosting address from getaddrinfo().
  if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
  {
		fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(status));
		exit(1);
	}

  // Try to bind the socket.
  for(p = servinfo; p != NULL; p = p->ai_next)
  {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
    {
			perror("socket() failed");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1)
    {
			perror("setsockopt() failed");
			exit(1);
		}
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &y, BUFFER_SIZE) == -1)
    {
			perror("setsockopt() failed");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
    {
			close(sockfd);
			perror("bind() failed");
			continue;
		}
    
		break;
	}
  freeaddrinfo(servinfo);

  // Check that we did successfully bind something.
  if (p == NULL)
  {
		fprintf(stderr, "couldn't bind socket\n");
		exit(1);
	}

  return sockfd;
}

// void wait_children(int s)
void wait_children()
{
  // (void)s;
  int e = errno;
  while (waitpid(-1, NULL, WNOHANG) > 0);
  errno = e;
}
