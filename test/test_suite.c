#include "base64_test.h"
#include "hashmap_test.h"
#include "linked_list_test.h"
#include "websocket_test.h"
#include <stdio.h>

int main() {
  printf("#----- Running test suite...\n");
//  hashmap_tests();
  linked_list_tests();
//  base64_tests();
//  websocket_tests();
  printf("#----- Test suite complete.\n");
  return 0;
}
