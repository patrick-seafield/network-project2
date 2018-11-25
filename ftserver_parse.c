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
#include "ftserver_parse.h"

// Turn the buffer[BUFFER_SIZE] into a struct describing
// the wishes of our client.
struct command * parse_request_text(char * buffer)
{
  struct command * cmd = malloc(sizeof(cmd));
  cmd->ctype = unknown;
  cmd->port = NULL;
  cmd->requested_file = NULL;

  // First, check the command type.
  char * command_name = strtok(buffer, " ");
  if (strcmp("-l", command_name) == 0)
  {
    cmd->ctype = list_dir;
    
  }
  else if (strcmp("-g", command_name) == 0)
  {
    cmd->ctype = send_data;

    char * file_name = strtok(NULL, " ");
    cmd->requested_file = malloc(strlen(file_name));
  }

  return cmd;
}

// Free all of the memory allocated for a struct command pointer.
void free_command(struct command * cmd)
{
  if (cmd->port != 0)
  {
    free(cmd->port);
  }
  if (cmd->requested_file != 0)
  {
    free(cmd->requested_file);
  }
  free(cmd);
}
