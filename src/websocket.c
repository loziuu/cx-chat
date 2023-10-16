#include "base64.h"
#include "hashmap.h"
#include "iterator.h"
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *switching_protocols_response = 
    "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: "
    "Upgrade\nSec-WebSocket-Accept: \n\n";
int default_response_len = 135; 

char *hello_world_resp = 
    "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 11\n\nHello World";

char *websocket_decode_key(char *client_key) {
  unsigned char *digest;
  char *concat;
  int key_len = strlen(client_key);

  digest = malloc(20);
  concat = calloc(key_len + magic_len + 1, sizeof(char)); // 1 for /0

  //
  memcpy(concat, client_key, key_len);
  memcpy(concat + key_len, magic_string, magic_len);
  concat[key_len + magic_len] = '\0';

  CC_SHA1_GEN((unsigned char *)concat, key_len + magic_len, digest);
  char *result = base64_encode_allocate(digest, 20);

  free(concat);
  free(digest);
  return result;
}

void websocket_handle(int *connfd) {
  char request[65535];

  // Read in loop, for now it's just bulk read into mem.
  read(*connfd, request, sizeof(request));

  LinkedList *lines = str_split_lines(request);
  Node *node = lines->head;

  printf("Printing request lines: \n");
  while (node != 0) {
    printf("%s\n", (char *)node->data);
    node = node->next;
  }
  linked_list_free(lines);

  // handle connection I guess
  write(*connfd, switching_protocols_response, default_response_len);
  memset(request, 0, sizeof(request));
}

// Move hashmap to be passed as a argument :)
HashMap *parse_request(Iterator *request_lines_iter) {
  HashMap *request = hashmap_init();
  Node *node = request_lines_iter->node;

  // Parse first line, [HTTP_METHOD HTTP_PATH HTTP_VERSION]
  LinkedList *words = str_split(node->data, ' ');

  Iterator *words_iter = iter_from_linked_list(words);

  hashmap_put(request, "method", iter_next(words_iter)->data);
  hashmap_put(request, "path", iter_next(words_iter)->data);
  hashmap_put(request, "version", iter_next(words_iter)->data);

  iter_free(words_iter);
  linked_list_free(words);
  return request;
}

void websocket_handle_new_connection(int *connfd) {
  char request[65535];

  read(*connfd, request, sizeof(request));
  
  if (strstr(request, "echo") != NULL) {
    printf("Echo!\n");
    return;
  }

  LinkedList *lines = str_split_lines(request);
  Iterator *iter = iter_from_linked_list(lines);

  HashMap *request_map = parse_request(iter);
  char *method = hashmap_get(request_map, "method");
  char *path = hashmap_get(request_map, "path");
  char *version = hashmap_get(request_map, "version");

  write(*connfd, hello_world_resp, strlen(hello_world_resp));
  memset(request, 0, sizeof(request));

  hashmap_free(request_map);
  iter_free(iter);
  linked_list_free(lines);
}
