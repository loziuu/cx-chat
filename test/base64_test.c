#include "../src/base64.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_encode() {
  char *val = "Many hands make light work.";
  char *result = malloc(64);

  base64_encode(val, result, strlen(val));

  assert(strcmp(result, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu") == 0);
}

void test_encode_with_padding() {
  char *val = "light work.";
  char *result = malloc(64);

  base64_encode(val, result, strlen(val));

  assert(strcmp(result, "bGlnaHQgd29yay4=") == 0);
}

void endcode_and_compare(char *val, char *expected) {
  char *result = base64_encode_allocate(val, strlen(val));
  assert(strcmp(result, expected) == 0);
  free(result);
}

void test_encode_auto_allocated() {
  endcode_and_compare("light work.", "bGlnaHQgd29yay4=");
  endcode_and_compare("light work", "bGlnaHQgd29yaw==");
  endcode_and_compare("light wor", "bGlnaHQgd29y");
  endcode_and_compare("light wo", "bGlnaHQgd28=");
  endcode_and_compare("light w", "bGlnaHQgdw==");
}

void base64_tests() {
  test_encode();
  test_encode_with_padding();
  test_encode_auto_allocated();
  printf("All base64 tests... success!\n");
}
