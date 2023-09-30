/*
 *  Client program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT	12345		/* should be over 1024 */
#define BUF_SIZE	1024		/* block transfer size */

int fatal(char *str1, char *str2) {
  fprintf(stderr, str1, str2);
  exit(-1);
}


int main(int argc, char *argv[]) {
  int var_return,
  	  socket_client;
  char buf[BUF_SIZE];	/* buffer for incoming line */
  struct hostent	*host;		/* info about server */
  struct sockaddr_in	channel;	/* holds IP address */

  if(argc < 3)
    fatal("Usage: %s <server-IP> <message>\n", argv[0]);

  host = gethostbyname(argv[1]);	/* get server's IP address */
  if(!host)
    fatal("%s: gethostbyname() failed\n", argv[0]);

  socket_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(socket_client < 0)
    fatal("%s: socket() failed\n", argv[0]);

  memset(&channel, 0, sizeof(channel));
  channel.sin_family = AF_INET;
  memcpy(&channel.sin_addr.s_addr, host->h_addr, host->h_length);
  channel.sin_port = htons(SERVER_PORT);

  var_return = connect(socket_client, (struct sockaddr *)&channel, sizeof(channel));
  if(var_return < 0)
    fatal("%s: connect() failed\n", argv[0]);

  write(socket_client, argv[2], (strlen(argv[2]) + 1));

  close(socket_client);
}
