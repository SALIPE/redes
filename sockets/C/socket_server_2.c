/*
 *  Server program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SERVER_PORT	12345		/* should be over 1024 */
#define BUF_SIZE	1024		/* block transfer size */
#define QUEUE_SIZE	10		/* maximum no of pending reqs */

#define SERVER_MSG	"I am the server"

int fatal(char *str1, char *str2) {
  fprintf(stderr, str1, str2);
  exit(-1);
}

int main(int argc, char *argv[]) {
  int server_socket,
  	  var_return,
  	  on,
      flag;
  char buf[BUF_SIZE];	/* buffer for incoming line */
  struct sockaddr_in	channel;	/* holds IP address */
  struct sockaddr_in	channel_client;
  int addlen = sizeof(channel_client);

  memset(&channel, 0, sizeof(channel));	/* make all-zeros */
  channel.sin_family = AF_INET;
  channel.sin_addr.s_addr = htonl(INADDR_ANY);
  channel.sin_port = htons(SERVER_PORT);

  server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(server_socket < 0)
    fatal("%s: socket() failed\n", argv[0]);

  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

  var_return = bind(server_socket, (struct sockaddr *)&channel, sizeof(channel));
  if(var_return < 0)
    fatal( "%s: bind() failed\n", argv[0]);

  flag = 1;
  while(flag){
    printf("%s\n", SERVER_MSG);
    recvfrom(server_socket, buf, BUF_SIZE, 0, (struct sockaddr *)&channel_client, &addlen);

    printf("%s received from %s:%d\n%s\n", argv[0], inet_ntoa(channel_client.sin_addr), ntohs(channel_client.sin_port), buf);

    if(strcmp(buf, "over") == 0) {
      close(server_socket);
      flag = 0;
    }
  }
}
