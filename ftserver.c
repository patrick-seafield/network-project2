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
#include "ftserver_parse.h"
#include "ftserver_respond.h"

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
  printf("Server open on %s\n", argv[1]);
  
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

      // Announce our new connection.
      char s[INET_ADDRSTRLEN];
      inet_ntop(client_addr.ss_family,
                &((struct sockaddr_in *)&client_addr)->sin_addr,
                s, sizeof s);
      printf("Connection from %s.\n", s);

      // Receive a command from the client.
      char * buffer = malloc(BUFFER_SIZE);
      memset(buffer, '\0', BUFFER_SIZE);
      int bytes_recv;

      if ((bytes_recv = recv(acceptfd, buffer, BUFFER_SIZE - 1, 0)) == -1)
      {
        perror("recv() failed");
        exit(1);
      }

      // Parse the command sent by the client.
      struct command * cmd = parse_request_text(buffer);

      if (cmd->ctype == list_dir)
      {
        printf("List directory requested on port %s.\n", cmd->port);

        // List the directory files for downloading.
        if (list_directory(acceptfd, cmd) == -1)
        {
          perror("list_directory() failed");
          exit(1);
        }
      }
      else if (cmd->ctype == send_data)
      {
        printf("File “%s” requested on port %s.\n", cmd->requested_file, cmd->port);
        
        // Send the requested file to the client on the specified 
        if (send_file(acceptfd, cmd) == -1)
        {
          perror("send_file() failed");
          exit(1);
        }
      }
      else
      {
        // Respond that we don't know what the heck you are asking for!
        if (respond_unsure(acceptfd) == -1)
        {
          perror("respond_unsure() failed");
          exit(1);
        }
      }

      // Close remaining file descriptor, free, and exit.
      free(buffer);
      free_command(cmd);
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
