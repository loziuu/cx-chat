#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct {
  struct Node *head;
  struct Node *tail;
} LinkedList;

LinkedList *linked_list_new();
int node_has_next(Node *node);

void linked_list_push(LinkedList *list, void *data, size_t size);
void *linked_list_pop(LinkedList *list);

void linked_list_free(LinkedList *list);

LinkedList *str_split(char *data, char delim);
LinkedList *str_split_lines(char *data);
LinkedList *str_split_bytes(uint8_t *data, size_t size, char delim);

#endif
