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
#include <arpa/inet.h>

#define SERVER_PORT 12345 /* should be over 1024 */
#define BUF_SIZE 1024     /* block transfer size */

int fatal(char *str1, char *str2)
{
  fprintf(stderr, str1, str2);
  exit(-1);
}

int main(int argc, char *argv[])
{
  int socket_client;
  int receive_number;
  char buf[BUF_SIZE];         /* buffer for incoming line */
  struct hostent *host;       /* info about server */
  struct sockaddr_in channel; /* holds IP address */

  if (argc < 2)
    fatal("Usage: %s <server-name> <message>\n", argv[0]);

  host = gethostbyname("127.0.0.1"); /* get server's IP address */
  if (!host)
    fatal("%s: gethostbyname() failed\n", "127.0.0.1");

  socket_client = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socket_client < 0)
    fatal("%s: socket() failed\n", argv[0]);

  memset(&channel, 0, sizeof(channel));
  channel.sin_family = AF_INET;
  memcpy(&channel.sin_addr.s_addr, host->h_addr, host->h_length);
  channel.sin_port = htons(SERVER_PORT);

  receive_number = atoi(argv[1]);

  if (receive_number > 0)
  {
    sendto(socket_client, argv[1], (strlen(argv[1]) + 1), 0, (struct sockaddr *)&channel, sizeof(channel));
  }
  else
  {
    fatal("%s: Number needs be greater than 0\n", argv[1]);
  }

  close(socket_client);
  exit(0);
}
