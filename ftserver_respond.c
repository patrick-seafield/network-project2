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
#include "ftserver_respond.h"

int list_directory(int acceptfd, struct command * cmd)
{
  int datafd, bytes_send;
  // bytes_send = send(acceptfd, "Hello, folks!", 13, 0);
  bytes_send = send(acceptfd, "OK-l", 5, 0);

  // datafd = ftserver_bind(cmd->port);

  return bytes_send;
}

int send_file(int acceptfd)
{
  return 0;
}


int respond_unsure(int acceptfd)
{
  return send(acceptfd, "ERROR: Sorry, I didn't catch that!\n", 36, 0);
}
