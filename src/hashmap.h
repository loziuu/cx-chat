#ifndef HASHMAP_H
#define HASHMAP_H

#include "linked_list.h"
#include <stdint.h>

#define HASHMAP_BUCKETS 11

typedef uint32_t hash_t;

struct HashMapNode {
  char *key;
  hash_t hash;
  void *data;
  struct HashMapNode *next;
};

struct HashMapBucket {
  struct HashMapNode *head;
};

struct HashMap {
  int size;
  struct HashMapBucket *buckets;
};

struct HashMap *hashmap_init();

void hashmap_put(struct HashMap *map, char *key, void *data);

void *hashmap_get(struct HashMap *map, char *key);

void hashmap_free(struct HashMap *map);

#endif
