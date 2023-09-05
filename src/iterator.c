#include "iterator.h"
#include <stdio.h>

struct Iterator iter_from_linked_list(struct LinkedList *list) {
  struct Iterator iterator;
  iterator.node = list->head;
  return iterator;
}

struct Node* iter_next(struct Iterator *iterator) {
  struct Node* val = iterator->node;
  iterator->node = iterator->node->next; 
  return val;
}

int has_next(struct Iterator *iterator) {
  return iterator->node != 0;
}

