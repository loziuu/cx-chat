#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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

#endif
