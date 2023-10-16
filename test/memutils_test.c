#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../src/memutils.h"
#include "memutils_test.h"

void test_concat() {
  char *first = "Hello";
  char *second = "World";

  String *result = memutils_concat(first, second);

  assert(strcmp(result->ptr, "HelloWorld") == 0);
}

void memutils_tests() {
  test_concat();
  printf("All memutils tests... success!\n");
}
