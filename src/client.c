#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

char* websocket_connect_request() {
  return "GET / HTTP/1.1\r\n"
         "Host: localhost:42069\r\n"
         "Connection: Upgrade\r\n"
         "Upgrade: websocket\r\n"
         "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n" // TODO: Verify what the fuck is going on here?
         "Sec-WebSocket-Version: 13\r\n\r\n"; // TODO: Same as above
}

/*
int main() {
  struct sockaddr_in addr;
  int serverfd;
  int sock;

  addr = (struct sockaddr_in){.sin_family = AF_INET,
                                     .sin_port = htons(42069),
                                     .sin_addr.s_addr = INADDR_ANY};

  sock = socket(AF_INET, SOCK_STREAM, 0);

  serverfd = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
  if (serverfd < 0) {
    return errno;
  }
  send(sock, "GET / HTTP/1.1\r\n\r\n", 20, 0);
  return 0;
}
*/
