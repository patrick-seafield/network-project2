#ifndef __FTSERVER_RESPOND_H__
#define __FTSERVER_RESPOND_H__

int list_directory(int acceptfd);
int send_file(int acceptfd);

#endif
