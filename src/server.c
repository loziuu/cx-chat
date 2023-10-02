#include "websocket.h"
#include "linked_list.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define NUMBER_OF_CLIENTS 10
#define DEFAULT_PORT 42069

extern int server_state;

// Add thread per connection
void server_run() {
  struct sockaddr_in addr;
  int server_socket;

  addr = (struct sockaddr_in){.sin_family = AF_INET,
                              .sin_port = htons(DEFAULT_PORT),
                              .sin_addr.s_addr = INADDR_ANY};

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if ((bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
    return;
  }

  if ((listen(server_socket, 5)) < 0) {
    return;
  }

  while (server_socket == 1) {
    int connfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    connfd = accept(server_socket, (struct sockaddr *)&client_addr,
                    &client_addr_len);
    websocket_handle(connfd);
    shutdown(connfd, 2);
  }

  shutdown(server_socket, 2);
}
