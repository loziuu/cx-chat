#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memutils.h"

LinkedList *linked_list_new() {
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = 0;
  list->tail = 0;
  return list;
}

int node_has_next(Node *node) { return node->next != 0; }

// Where does head point at after second push?
void linked_list_push(LinkedList *list, void *data, size_t size) {
  if (list->head == 0) {
    list->head = malloc(sizeof(Node));
    list->head->data = memutils_copy(data, size);
    list->head->next = 0;
    list->tail = list->head;
  } else {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = memutils_copy(data, size);
    new_node->next = 0;
    list->tail->next = new_node;
    list->tail = new_node;
  }
}

LinkedList *str_split(char *data, char delim) {
  LinkedList *list = linked_list_new();
  int data_len = strlen(data);

  int start = 0;

  for (int i = 0; i <= data_len; i++) {
    if (data[i] == delim || data[i] == '\0' || i == data_len) {
      int size = i - start + 1;
      char *line = calloc(size+1, sizeof(char));
      memcpy(line, data + start, i - start);
      line[size] = '\0';
      linked_list_push(list, (void *)line, size);
      start = i + 1;
      free(line);
    }
  }

  return list;
}

// So far copying lines to new mem place.
// It's eager now. can we do it lazily? Somehow?
LinkedList *str_split_lines(char *data) {
  return str_split(data, '\n');
}

void node_free(Node *node) {
  if (node == 0) {
    return;
  }
  node_free(node->next);
  free(node->data);
  free(node);
}

void linked_list_free(LinkedList *list) {
  Node *node = list->head;
  if (node != 0) {
    node_free(node);
  }
  free(list);
}

void *linked_list_pop(LinkedList *list) {
  Node *node = list->head;
  if (node != 0) {
    list->head = node->next;
    void *data = node->data;
    free(node);
    return data; 
  }
  return 0;
}
