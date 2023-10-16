#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memutils.h"

void *memutils_copy(const void *src, size_t size) {
  void *dest = malloc(size);
  if (dest == NULL) {
    printf("Failed to allocate memory for copy.\n");
    exit(1);
  }
  memcpy(dest, src, size);
  return dest;
}

// Make it not using strlen
String *memutils_concat(const char *first, const char *second) {
  String *result = malloc(sizeof(String)); 

  int f_len = strlen(first);
  int s_len = strlen(second);
  int len = f_len + s_len + 1;
  char *concatenated = malloc(len);

  memcpy(concatenated, first, f_len);
  memcpy(concatenated + f_len, second, s_len);
  concatenated[len-1] = '\0';

  result->ptr = concatenated;
  result->length = len;

  return result;
}
