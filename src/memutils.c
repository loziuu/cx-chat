#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *memutils_copy(const void *src, size_t size) {
  void *dest = malloc(size);
  if (dest == NULL) {
    printf("Failed to allocate memory for copy.\n");
    exit(1);
  }
  memcpy(dest, src, size);
  return dest;
}
