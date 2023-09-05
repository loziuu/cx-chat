#include "linked_list.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define NUMBER_OF_CLIENTS 10
#define DEFAULT_PORT 42069

char *default_response =
    "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, "
    "world!</h1></body></html>";

int main() {
  struct sockaddr_in addr;
  int server_socket;
  int va;

  addr = (struct sockaddr_in){.sin_family = AF_INET,
                              .sin_port = htons(DEFAULT_PORT),
                              .sin_addr.s_addr = INADDR_ANY};

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if ((bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
    return errno;
  }

  if ((listen(server_socket, 5)) < 0) {
    return errno;
  }

  while (1) {
    int connfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    connfd = accept(server_socket, (struct sockaddr *)&client_addr,
                    &client_addr_len);

    char request[65535];

    // Read in loop, for now it's just bulk read into mem.
    read(connfd, request, sizeof(request));

    struct LinkedList lines = str_split_lines(request);
    struct Node *node = lines.head;

    printf("Printing request lines: \n");
    while (node != 0) {
      printf("%s\n", (char *)node->data);
      node = node->next;
    }
    linked_list_free(&lines);

    // handle connection I guess
    write(connfd, default_response, strlen(default_response));
    memset(request, 0, sizeof(request));
    shutdown(connfd, 2);
  }

  shutdown(server_socket, 2);
}
