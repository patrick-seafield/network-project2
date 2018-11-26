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
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "constants.h"
#include "ftserver_bind.h"
#include "ftserver_respond.h"

int list_directory(int acceptfd, struct command * cmd)
{
  int data_socketfd, data_acceptfd, bytes_send;

  // Bind to the data port requested by the client.
  struct sockaddr_storage client_addr;
  socklen_t addr_size = sizeof client_addr;

  printf("Binding to data port %s.\n", cmd->port);
  data_socketfd = ftserver_bind(cmd->port);

  printf("Listening on data_socketfd.\n");
  if (listen(data_socketfd, 1) == -1)
  {
    perror("list_directory: listen() failed");
    exit(1);
  }

  // Send an acknowledgement that the request was good.
  bytes_send = send(acceptfd, "OK-l", 5, 0);

  // Accept a connection we expect from the client on the separate data port.
  printf("Calling accept() on data_socketfd.\n");
  data_acceptfd = accept(data_socketfd, (struct sockaddr *)&client_addr, &addr_size);
  if (data_acceptfd == -1)
  {
    perror("data port accept() failed");
    exit(1);
  }
  
  // Announce our new data connection.
  char s[INET_ADDRSTRLEN];
  inet_ntop(client_addr.ss_family,
            &((struct sockaddr_in *)&client_addr)->sin_addr,
            s, sizeof s);
   printf("Sending directory contents to %s:%s.\n", s, cmd->port);

  // Send the directory contents to the client.
  struct dirent *ep;
  DIR * dp = opendir("./");
  if (dp == NULL)
  {
    perror("Couldn't open directory: opendir() failed");
    exit(1);
  }

  while ((ep = readdir(dp)) != NULL)
  {
    if (ep->d_type == DT_REG)
    {
      send(data_acceptfd, ep->d_name, strlen(ep->d_name), 0);
    }
  }

  close(data_socketfd);
  close(data_acceptfd);
  return bytes_send;
}

int send_file(int acceptfd, struct command * cmd)
{
  FILE * fp = fopen(cmd->requested_file, "r");
  if (fp == NULL)
  {
    printf("Problem with %s\n", cmd->requested_file);
    perror("Couldn't open requested file.");

    return send(acceptfd, "FILE NOT FOUND", 15, 0);
  }

  int data_socketfd, data_acceptfd, bytes_send;

  // Bind to the data port requested by the client.
  struct sockaddr_storage client_addr;
  socklen_t addr_size = sizeof client_addr;

  printf("Binding to data port %s.\n", cmd->port);
  data_socketfd = ftserver_bind(cmd->port);

  printf("Listening on data_socketfd.\n");
  if (listen(data_socketfd, 1) == -1)
  {
    perror("list_directory: listen() failed");
    exit(1);
  }

  // Send an acknowledgement that the request was good.
  bytes_send = send(acceptfd, "OK-g", 5, 0);

  // Accept a connection we expect from the client on the separate data port.
  printf("Calling accept() on data_socketfd.\n");
  data_acceptfd = accept(data_socketfd, (struct sockaddr *)&client_addr, &addr_size);
  if (data_acceptfd == -1)
  {
    perror("data port accept() failed");
    exit(1);
  }
  
  // Announce our new data connection.
  char s[INET_ADDRSTRLEN];
  inet_ntop(client_addr.ss_family,
            &((struct sockaddr_in *)&client_addr)->sin_addr,
            s, sizeof s);
   printf("Sending file contents to %s:%s.\n", s, cmd->port);

   // Send the file contents to the client.
   char * buffer = malloc(BUFFER_SIZE);
   size_t fread_bytes;

   while (!feof(fp))
   {
     memset(buffer, '\0', BUFFER_SIZE);
     fread_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, fp);

     if (ferror(fp))
     {
       perror("Problem reading from file. fread() failed.");
       exit(1);
     }

     send(data_acceptfd, buffer, strlen(buffer), 0);
   }

  close(data_socketfd);
  close(data_acceptfd);
  return bytes_send;
}


int respond_unsure(int acceptfd)
{
  return send(acceptfd, "ERROR: Sorry, I didn't catch that!\n", 36, 0);
}
