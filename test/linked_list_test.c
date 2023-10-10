#include "../src/linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void compare_node_value(void *node, char *expected_value) {
  assert(strcmp((char *) node, expected_value) == 0);
  free(node);
}

void push_two() {
  LinkedList *list = linked_list_new();

  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "World", 6);

  compare_node_value(linked_list_pop(list), "Hello");
  compare_node_value(linked_list_pop(list), "World");
  linked_list_free(list);
}

void push_three() {
  LinkedList *list = linked_list_new();

  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "Darkness", 9);
  linked_list_push(list, "My old friend", 14);

  compare_node_value(linked_list_pop(list), "Hello");
  compare_node_value(linked_list_pop(list), "Darkness");
  compare_node_value(linked_list_pop(list), "My old friend");
  linked_list_free(list);
}

void push_four() {
  LinkedList *list = linked_list_new();

  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "Darkness", 9);
  linked_list_push(list, "My old friend", 14);
  linked_list_push(list, "ASD", 4);

  compare_node_value(linked_list_pop(list), "Hello");
  compare_node_value(linked_list_pop(list), "Darkness");
  compare_node_value(linked_list_pop(list), "My old friend");
  compare_node_value(linked_list_pop(list), "ASD");
  linked_list_free(list);
}

void linked_list_tests() {
  push_two();
  push_three();
  push_four();
  printf("All linked list tests... success!\n");
}
