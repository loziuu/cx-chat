#ifndef ITERATOR_H
#define ITERATOR_H

#include "linked_list.h"

typedef struct {
  Node *node;
} Iterator;

Iterator *iter_from_linked_list(LinkedList *list);
Node *iter_next(Iterator *iter);
uint8_t *iter_next_value(Iterator *iter);
void iter_free(Iterator *iter);

#endif
