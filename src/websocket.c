#include "base64.h"
#include "linked_list.h"

#include <CommonCrypto/CommonCrypto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *magic_string = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
int magic_len = 36;

char *default_response =
    "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: "
    "Upgrade\nSec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\n\n";

char *websocket_decode_key(char *client_key) {
  int key_len = strlen(client_key);
  char *concat = malloc(key_len + magic_len + 1); // 1 for /0
  memcpy(concat, client_key, key_len);
  memcpy(concat + key_len, magic_string, magic_len);
  unsigned char *digest = malloc(CC_SHA1_DIGEST_LENGTH);
  CC_SHA1(concat, key_len + magic_len, digest);
  return base64_encode_allocate(digest, CC_SHA1_DIGEST_LENGTH);
}

void websocket_handle(int connfd) {
  char request[65535];

  // Read in loop, for now it's just bulk read into mem.
  read(connfd, request, sizeof(request));

  struct LinkedList *lines = str_split_lines(request);
  struct Node *node = lines->head;

  printf("Printing request lines: \n");
  while (node != 0) {
    printf("%s\n", (char *)node->data);
    node = node->next;
  }
  linked_list_free(lines);

  // handle connection I guess
  write(connfd, default_response, strlen(default_response));
  memset(request, 0, sizeof(request));
}
