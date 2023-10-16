#ifndef MEMUTILS_H
#define MEMUTILS_H

#include <stdlib.h>

typedef struct {
  char *ptr;
  int length;
} String;

void *memutils_copy(const void *src, size_t size);
String *memutils_concat(const char *from, const char *to);

#endif
