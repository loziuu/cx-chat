#include "../src/iterator.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_no_split() {
  LinkedList* list = linked_list_new();

  linked_list_push(list, "hello", 6);
  linked_list_push(list, "world", 6);

  Iterator *iter = iter_from_linked_list(list);

  assert(strcmp(iter_next(iter)->data, "hello") == 0);
  assert(strcmp(iter_next(iter)->data, "world") == 0);
  iter_free(iter);
  linked_list_free(list);
}

void test_simple_linked_list() {
  LinkedList *list = str_split("hello\nworld", '\n');
  Iterator *iter = iter_from_linked_list(list);

  assert(strcmp(list->head->data, "hello") == 0);
  assert(strcmp(list->tail->data, "world") == 0);
  iter_free(iter);
  linked_list_free(list);
}

void test_split_string_whitespace() {
  LinkedList *list = str_split("hello world", ' ');

  assert(strcmp(list->head->data, "hello") == 0);
  assert(strcmp(list->tail->data, "world") == 0);
  linked_list_free(list);
}

void test_http_json_request() {
  LinkedList *list =
      str_split_lines("GET / HTTP/1.1\nHost: localhost:42069\nUser-Agent: "
                      "curl/7.64.1\nAccept: */*\n\n{\"msg\":\"Test\"}");

  Iterator *iter = iter_from_linked_list(list);
  assert(strcmp(iter_next(iter)->data, "GET / HTTP/1.1") == 0);
  assert(strcmp(iter_next(iter)->data, "Host: localhost:42069") == 0);
  assert(strcmp(iter_next(iter)->data, "User-Agent: curl/7.64.1") == 0);
  assert(strcmp(iter_next(iter)->data, "Accept: */*") == 0);
  assert(strcmp(iter_next(iter)->data, "") == 0);
  assert(strcmp(iter_next(iter)->data, "{\"msg\":\"Test\"}") == 0);
  iter_free(iter);
  linked_list_free(list);
}

void iterator_tests() {
  test_no_split();
  test_http_json_request();
  test_simple_linked_list();
  test_split_string_whitespace();
  printf("All iterator tests... success!\n");
}
