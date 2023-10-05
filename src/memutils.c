#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *memutils_copy(void *src, size_t size) {
  void *dest = malloc(size);
  memcpy(dest, src, size);
  return dest;
}
