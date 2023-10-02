#include "../src/iterator.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int test_simple_linked_list() {
  struct LinkedList *list = str_split_lines("hello\nworld");

  struct Iterator iter = iter_from_linked_list(list);
  assert(strcmp(list->head->data, "hello") == 0);
  assert(strcmp(list->tail->data, "world") == 0);
  linked_list_free(list);
  return 0;
}

int test_http_json_request() {
  struct LinkedList *list =
      str_split_lines("GET / HTTP/1.1\nHost: localhost:42069\nUser-Agent: "
                      "curl/7.64.1\nAccept: */*\n\n{\"msg\":\"Test\"}");

  struct Iterator iter = iter_from_linked_list(list);
  assert(strcmp(iter_next(&iter)->data, "GET / HTTP/1.1") == 0);
  assert(strcmp(iter_next(&iter)->data, "Host: localhost:42069") == 0);
  assert(strcmp(iter_next(&iter)->data, "User-Agent: curl/7.64.1") == 0);
  assert(strcmp(iter_next(&iter)->data, "Accept: */*") == 0);
  assert(strcmp(iter_next(&iter)->data, "") == 0);
  assert(strcmp(iter_next(&iter)->data, "{\"msg\":\"Test\"}") == 0);
  linked_list_free(list);
  return 0;
}

int test_split_string_whitespace() {
  struct LinkedList *list = str_split("hello world", ' ');

  assert(strcmp(list->head->data, "hello") == 0);
  assert(strcmp(list->tail->data, "world") == 0);
  linked_list_free(list);
  return 0;
}

void linked_list_tests() {
  test_simple_linked_list();
  test_split_string_whitespace();
  test_http_json_request();
  printf("All linked list tests... success!\n");
}
