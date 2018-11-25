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
#include "ftserver_respond.h"

int list_directory(int acceptfd, struct command * cmd)
{
  int bytes_send;
  bytes_send = send(acceptfd, "Hello, folks!", 13, 0);

  return bytes_send;
}

int send_file(int acceptfd)
{
  return 0;
}

