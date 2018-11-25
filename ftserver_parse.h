#ifndef __FTSERVER_PARSE_H__
#define __FTSERVER_PARSE_H__

enum command_type {
  unknown,
  list_dir,
  send_data
};

struct command {
  enum command_type ctype;
  char * port;
  char * requested_file;
  // char * directory_to_list;
};

struct command * parse_request_text(char * buffer);
void free_command(struct command * cmd);

#endif
