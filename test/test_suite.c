#include "base64_test.h"
#include "hashmap_test.h"
#include "iterator_test.h"
#include "linked_list_test.h"
#include "websocket_test.h"
#include <stdio.h>

int main() {
  printf("#----- Running test suite...\n");
  iterator_tests();
  websocket_tests();
  linked_list_tests();
  hashmap_tests();
  base64_tests();
  printf("#----- Test suite complete.\n");
  return 0;
}
