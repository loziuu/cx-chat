#include "base64.h"
#include "linked_list.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const char *magic_string = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
const int magic_len = 36;

#ifdef __APPLE__
#include <CommonCrypto/CommonDigest.h>
#define SHA_DIGEST_LEN CC_SHA1_DIGEST_LENGTH
#define CC_SHA1_GEN CC_SHA1
#endif

#ifdef unix
#define SHA_DIGEST_LEN SHA_DIGEST_LENGTH
#include <openssl/sha.h>
#define CC_SHA1_GEN SHA1
#endif

char *default_response =
    "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: "
    "Upgrade\nSec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\n\n";

char *websocket_decode_key(char *client_key) {
  unsigned char *digest;
  char *concat;

  int key_len = strlen(client_key);
  concat = calloc(key_len + magic_len + 1, sizeof(char)); // 1 for /0
                                                          //
  memcpy(concat, client_key, key_len);
  memcpy(concat + key_len, magic_string, magic_len);
  concat[key_len + magic_len] = '\0';

  digest = malloc(20);

  CC_SHA1_GEN((unsigned char *)concat, key_len + magic_len, digest);
  char *result = base64_encode_allocate(digest, 20);

  free(concat);
  free(digest);
  return result;
}

// TODO: Make a loop that reads in chunks of 1024 bytes.
// TODO: Clean up after return
void websocket_handle(int *connfd) {
  uint8_t request[65535];
  //
  // Read in loop, for now it's just bulk read into mem.
  int status = 1;

  while ((write(*connfd, "ping", 4)) > 0) {
    status = read(*connfd, request, sizeof(request));

    if (status < 0) {
      printf("Error reading from socket.\n");
      break;
    }

    LinkedList *lines = str_split_bytes(request, status, '\n');
    Node *node = lines->head;

    printf("Printing request lines: \n");
    while (node != 0) {
      printf("%s\n", (char *)node->data);
      node = node->next;
    }
    linked_list_free(lines);

    // handle connection I guess
    memset(request, 0, sizeof(request));
  }
  printf("Disconnecting...\n");
  shutdown(*connfd, 2);
}
