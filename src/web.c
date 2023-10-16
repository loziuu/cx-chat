#include "atomic.h"
#include "web.h"
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define NUMBER_OF_CLIENTS 10
#define HTTP_PORT 8080

extern AtomicInt *server_state;

char *response = "HTTP/1.1 200 OK\nContent-Length: 98\nContent-Type: text/html\n\n<html><body><script src=\"https://unpkg.com/htmx.org/dist/ext/ws.js\"></script> Test</body></html>";


void serve(int connfd) {
  char request[65535];
  read(connfd, request, sizeof(request)); 
  write(connfd, response, strlen(response));
}


void run_web() {
  struct sockaddr_in addr;
  int server_socket;

  addr = (struct sockaddr_in){.sin_family = AF_INET,
                              .sin_port = htons(HTTP_PORT),
                              .sin_addr.s_addr = INADDR_ANY};

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if ((bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
    printf("[WEB] Error binding socket: %d\n", errno);
    return;
  }

  if ((listen(server_socket, NUMBER_OF_CLIENTS)) < 0) {
    printf("[WEB] Error listening on socket: %d\n", errno);
    return;
  }

  int result;
  // TODO: USE DEFINED CONSTANTS FOR STATE
  while ((result = atomic_read(server_state)) == 0) {
    int connfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    connfd = accept(server_socket, (struct sockaddr *)&client_addr,
                    &client_addr_len);
    serve(connfd);
    close(connfd);
  }

  printf("Shutting down the web server...");
  shutdown(server_socket, 2);
}
