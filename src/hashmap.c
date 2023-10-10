#include "hashmap.h"
#include "memutils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// MAKE BUCKETS LAZY!
HashMap *hashmap_init() {
  HashMap *map = malloc(sizeof(HashMap));

  for (int i = 0; i < HASHMAP_BUCKETS; i++) {
    HashMapBucket *bucket = malloc(sizeof(HashMapBucket));
    bucket->head = NULL;
    map->buckets[i] = bucket;
  }

  map->size = HASHMAP_BUCKETS;
  return map;
}

// DJB2 hash function
hash_t calculcate_hash(char *key) { 
  hash_t hash = 5831;
  char *c = key;

  while (*c != '\0') {
    hash = ((hash << 5) + hash) + *c; 
    c++;
  }

  return hash;
}

void hashmap_put(HashMap *map, char *key, void *data) {
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  HashMapBucket *bucket = map->buckets[bucket_index];

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
  new_node->next = 0;
  if (prev != NULL) {
    prev->next = new_node;
  } else { 
    bucket->head = new_node;
  }
}

void *hashmap_get(HashMap *map, char *key) { 
  hash_t hash = calculcate_hash(key);
  uint32_t bucket_index = hash % map->size;
  HashMapBucket *bucket = map->buckets[bucket_index];
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

void free_node(HashMapNode *node) {
  if (node == NULL) {
    return;
  }
  free_node(node->next);
  free(node);
}

void free_bucket(HashMapBucket *bucket) {
  free_node(bucket->head);
  free(bucket);
}

void hashmap_free(HashMap *map) {
  for (int i = 0; i < map->size; i++) {
    HashMapBucket *bucket = map->buckets[i];
    free_bucket(bucket);
  }
  free(map);
}
