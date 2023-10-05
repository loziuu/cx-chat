#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>

Iterator *iter_from_linked_list(LinkedList *list) {
  Iterator *iterator = malloc(sizeof(Iterator));
  iterator->node = list->head;
  return iterator;
}

Node *iter_next(Iterator *iterator) {
  Node *val = iterator->node;
  if (val == 0) {
    return 0;
  }
  iterator->node = iterator->node->next;
  return val;
}

int has_next(Iterator *iterator) { return iterator->node != 0; }

void iter_free(Iterator *iter) {
  free(iter);
}

