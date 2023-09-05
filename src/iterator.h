#include "linked_list.h"

struct Iterator {
  struct Node *node;
};

struct Iterator iter_from_linked_list(struct LinkedList* list);
struct Node* iter_next(struct Iterator *iter);
