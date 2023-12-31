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

#define SERVER_PORT 12345 /* should be over 1024 */
#define BUF_SIZE 1024     /* block transfer size */
#define QUEUE_SIZE 10     /* maximum no of pending reqs */

#define SERVER_MSG "I am the server"

int fatal(char *str1, char *str2)
{
  fprintf(stderr, str1, str2);
  exit(-1);
}

struct dados
{
  int numero;
  char nome[BUF_SIZE];
};

int main(int argc, char *argv[])
{
  int server_socket,
      var_return,
      on,
      flag;

  char buf[BUF_SIZE];         /* buffer for incoming line */
  struct sockaddr_in channel; /* holds IP address */
  struct sockaddr_in channel_client;
  int addlen = sizeof(channel_client);
  struct dados received;
  char result_buf[BUF_SIZE];

  memset(&channel, 0, sizeof(channel)); /* make all-zeros */
  channel.sin_family = AF_INET;
  channel.sin_addr.s_addr = htonl(INADDR_ANY);
  channel.sin_port = htons(SERVER_PORT);

  server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (server_socket < 0)
    fatal("%s: socket() failed\n", argv[0]);

  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

  var_return = bind(server_socket, (struct sockaddr *)&channel, sizeof(channel));
  if (var_return < 0)
    fatal("%s: bind() failed\n", argv[0]);

  flag = 1;
  while (flag)
  {
    printf("Servidor Ligado\n");
    recvfrom(server_socket, &received, sizeof(struct dados), 0, (struct sockaddr *)&channel_client, &addlen);

    printf("Mensagem recebida de %s\n", received.nome);
    // Aluno 1: Felipe Bueno = 2letra = 69
    // Aluno 2: Messias Magalhães = 77
    // received_number = atoi(buf);

    gcvt(((received.numero * 69.00) / 77.00), 6, result_buf);
    sendto(server_socket, result_buf, (strlen(result_buf) + 1), 0, (struct sockaddr *)&channel_client, sizeof(channel_client));
    if (strcmp(received.nome, "over") == 0)
    {
      close(server_socket);
      flag = 0;
    }
  }
}
