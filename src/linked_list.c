#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int node_has_next(struct Node *node) { return node->next != 0; }

void linked_list_push(struct LinkedList *list, void *data) {
  if (list->head == 0) {
    printf("Pushing %s as head.\n", (char *)data);
    list->head = malloc(sizeof(struct Node)); 
    list->head->data = data;
    list->tail = list->head;
  } else {
    printf("Pushing %s\n", (char *)data);
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = data;
    list->tail->next = new_node;
    list->tail = new_node;
  }
}

// So far copying lines to new mem place.
// It's eager now. can we do it lazily? Somehow?
struct LinkedList str_split_lines(char *data) {
  struct LinkedList list;
  int data_len = strlen(data);
  
  int start = 0;
  int end = data_len;

  for (int i = 0; i < data_len; i++) {
    if (data[i] == '\n') {

      char* line = calloc((i-start), sizeof(char));

      printf("Copying %d bytes\nFrom %d to %d.\n", i - start, start, start + (i-start));

      memcpy(line, data + start, start + (i - start));

      line[i - start] = '\0';

      linked_list_push(&list, (void*) line); 
      start = i + 1;
    }
  }

  return list;
}

// Will free everything in the list.
void linked_list_free(struct LinkedList *list) {
  struct Node *node = list->head;
  if (node != 0) {
    node_free(node);
  }
}

// Will free the data as well.
void node_free(struct Node *node) {
  if (node->next != 0) {
    node_free(node->next);
  }
  free(node->data);
  free(node);
}

