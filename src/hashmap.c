#include "hashmap.h"
#include <stdint.h>
#include <stdlib.h>

// MAKE BUCKETS LAZY!
struct HashMap *hashmap_init() {
  struct HashMap *map = malloc(sizeof(struct HashMap));
  map->buckets = calloc(HASHMAP_BUCKETS, sizeof(struct HashMapBucket *));
  map->size = HASHMAP_BUCKETS;
  return map;
}

hash_t calculcate_hash(char *key) { return 0; }

void hashmap_put(struct HashMap *map, char *key, void *data) {
  // Calculate the hash
  // Get the bucket
  // Check if the key exists
  // If it does, replace the data
  // If it doesn't, add it to the bucket
  // If the bucket is full, resize the hashmap, it's linked list so not really
  // If the hashmap is full, resize the hashmap, well... look above.
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  struct HashMapBucket *bucket = &map->buckets[bucket_index];

  struct HashMapNode *prev = NULL;
  struct HashMapNode *node = bucket->head;
  while (node != NULL) {
    if (node->hash == hash && node->key == key) {
      node->data = data; 
      return;
    }
    prev = node;
  }
  struct HashMapNode *new_node = malloc(sizeof(struct HashMapNode));
  new_node->hash = hash;
  new_node->key = key;
  new_node->data = data;
  prev->next = new_node;
}

void *hashmap_get(struct HashMap *map, char *key) { 
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  struct HashMapBucket *bucket = &map->buckets[bucket_index];
  if (bucket->head == NULL) {
    return NULL;
  }
  struct HashMapNode *node = bucket->head;
  while (node != NULL) {
    if (node->hash == hash) {
      return node->data;
    }
  }
  return 0;
}

void free_bucket(struct HashMapBucket *bucket) {
  struct HashMapNode *node = bucket->head;
  while (node != NULL) {
    struct HashMapNode *next = node->next;
    free(node);
    node = next;
  }
  free(bucket);
}

void hashmap_free(struct HashMap *map) {
  for (int i = 0; i < map->size; i++) {
    struct HashMapBucket *bucket = &map->buckets[i];
    free_bucket(bucket);
  }
  free(map);
}
