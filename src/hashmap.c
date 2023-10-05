#include "hashmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// MAKE BUCKETS LAZY!
HashMap *hashmap_init() {
  HashMap *map = malloc(sizeof(HashMap));
  map->buckets = calloc(HASHMAP_BUCKETS, sizeof(struct HashMapBucket *));
  map->size = HASHMAP_BUCKETS;
  return map;
}

hash_t calculcate_hash(char *key) { return 0; }

void hashmap_put(HashMap *map, char *key, void *data) {
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  HashMapBucket *bucket = &map->buckets[bucket_index];

  HashMapNode *prev = NULL;
  HashMapNode *node = bucket->head;
  while (node != NULL) {
    if (node->hash == hash && node->key == key) {
      node->data = data; 
      return;
    }
    prev = node;
  }
  HashMapNode *new_node = malloc(sizeof(HashMapNode));
  new_node->hash = hash;
  new_node->key = key;
  new_node->data = data;
  if (prev != NULL) {
    prev->next = new_node;
  } else { 
    bucket->head = new_node;
  }
}

void *hashmap_get(HashMap *map, char *key) { 
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  HashMapBucket *bucket = &map->buckets[bucket_index];
  if (bucket->head == NULL) {
    return 0;
  }
  struct HashMapNode *node = bucket->head;
  while (node != NULL) {
    if (node->hash == hash) {
      return node->data;
    }
  }
  return 0;
}

void free_bucket(HashMapBucket *bucket) {
  HashMapNode *node = bucket->head;
  while (node != NULL) {
    HashMapNode *next = node->next;
    free(node);
    node = next;
  }
  free(bucket);
}

void hashmap_free(HashMap *map) {
  for (int i = 0; i < map->size; i++) {
    HashMapBucket *bucket = &map->buckets[i];
    free_bucket(bucket);
  }
  free(map);
}
