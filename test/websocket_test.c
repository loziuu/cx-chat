#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/websocket.h"

void test_key_decode() {
  char *val = websocket_decode_key("dGhlIHNhbXBsZSBub25jZQ==");

  assert(strcmp(val, "s3pPLMBiTxaQ9kYGzzhZRbK+xOo=") == 0);
  free(val);
}

void websocket_tests() {
  test_key_decode();
  printf("All websockets tests... success!\n");
}
