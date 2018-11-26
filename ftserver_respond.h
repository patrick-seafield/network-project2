#ifndef __FTSERVER_RESPOND_H__
#define __FTSERVER_RESPOND_H__

#include "ftserver_parse.h"

int list_directory(int acceptfd, struct command * cmd);
int send_file(int acceptfd, struct command * cmd);
int respond_unsure(int acceptfd);

#endif
