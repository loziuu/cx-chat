#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node {
  void *data;
  struct Node *next;
};

struct LinkedList {
  struct Node *head;
  struct Node *tail;
};

int node_has_next(struct Node *node);
void linked_list_push(struct LinkedList *list, void *data);
struct LinkedList *str_split(char *data, char delim);
struct LinkedList *str_split_lines(char *data);
void linked_list_free(struct LinkedList *list);
void node_free(struct Node *list);

#endif
