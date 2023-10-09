#include "../src/linked_list.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void push_two() {
  LinkedList *list = linked_list_new();
  
  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "World", 6);
  
  assert(strcmp(linked_list_pop(list)->data, "Hello") == 0);
  assert(strcmp(linked_list_pop(list)->data, "World") == 0);
  linked_list_free(list);
}

void push_three() {
  LinkedList *list = linked_list_new();
  
  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "Darkness", 9);
  linked_list_push(list, "My old friend", 14);

  
  assert(strcmp(linked_list_pop(list)->data, "Hello") == 0);
  assert(strcmp(linked_list_pop(list)->data, "Darkness") == 0);
  assert(strcmp(linked_list_pop(list)->data, "My old friend") == 0);
  linked_list_free(list);
}

void push_four() {
  LinkedList *list = linked_list_new();
  
  linked_list_push(list, "Hello", 6);
  linked_list_push(list, "Darkness", 9);
  linked_list_push(list, "My old friend", 14);
  linked_list_push(list, "ASD", 4);
  
  assert(strcmp(linked_list_pop(list)->data, "Hello") == 0);
  assert(strcmp(linked_list_pop(list)->data, "Darkness") == 0);
  assert(strcmp(linked_list_pop(list)->data, "My old friend") == 0);
  assert(strcmp(linked_list_pop(list)->data, "ASD") == 0);
  linked_list_free(list);
}

void linked_list_tests() {
  push_two();
  push_three();
  push_four();
  printf("All linked list tests... success!\n");
}
