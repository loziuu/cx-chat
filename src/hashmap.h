#ifndef HASHMAP_H
#define HASHMAP_H

#include "linked_list.h"
#include <stdint.h>

#define HASHMAP_BUCKETS 11

typedef uint32_t hash_t;

typedef struct HashMapNode {
  char *key;
  hash_t hash;
  void *data;
  struct HashMapNode *next;
} HashMapNode;

typedef struct {
  HashMapNode *head;
} HashMapBucket;

typedef struct {
  int size;
  HashMapBucket *buckets[HASHMAP_BUCKETS];
} HashMap;

HashMap *hashmap_init();
void hashmap_put(HashMap *map, char *key, void *data);
void *hashmap_get(HashMap *map, char *key);
void hashmap_free(HashMap *map);

#endif
