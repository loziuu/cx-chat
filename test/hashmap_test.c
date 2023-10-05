#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/hashmap.h"

void test_hashmap_init() {
  HashMap *map = hashmap_init(); 
  hashmap_put(map, "Content-Type", "application/json");

  char* val = (char*) hashmap_get(map, "Content-Type");

  assert(strcmp(val, "application/json") == 0);
}

void test_empty_hashmap() {
  HashMap *map = hashmap_init(); 

  char* val = (char*) hashmap_get(map, "Content-Type");

  assert(val == 0);
}

void hashmap_tests(){
  test_hashmap_init();
  test_empty_hashmap();
  printf("All hashmap tests... success!\n");
}

