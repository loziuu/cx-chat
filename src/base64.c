#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char arr[64] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(void *val, char *buf, int len) {
  const uint8_t *val_ptr = (const uint8_t *)val;
  int i;
  int buff_i;
  int block_num = 0;
  int num_of_blocks;
  int padding;

  num_of_blocks = len / 3;
  padding = len % 3;
  if (padding != 0) {
    num_of_blocks++;
  }

  uint32_t block;
  uint8_t n1, n2, n3, n4;
  buff_i = 0;

  for (i = 0; i < num_of_blocks; i++) {
    block_num = i * 3;

    block = 0x0;
    block |= (val_ptr[block_num]) << 16;
    if (block_num + 1 < len) {
      block |= (val_ptr[block_num + 1]) << 8;
    }
    if (block_num + 2 < len) {
      block |= (val_ptr[block_num + 2]);
    }

    n1 = (block & 0xFC0000) >> 18;
    n2 = (block & 0x03F000) >> 12;
    n3 = (block & 0x000FC0) >> 6;
    n4 = (block & 0x00003F);

    buf[buff_i] = arr[n1];
    buff_i++;
    buf[buff_i] = arr[n2];
    buff_i++;
    if (block_num + 1 < len) {
      buf[buff_i] = arr[n3];
      buff_i++;
    }
    if (block_num + 2 < len) {
      buf[buff_i] = arr[n4];
      buff_i++;
    }
  }

  if (padding > 0) {
    for (; padding < 3; padding++) {
      buf[buff_i] = '=';
      buff_i++;
    }
  }

  buf[buff_i] = '\0';
}

void *base64_encode_allocate(void *val, int len) {
  int padding = len % 3;
  int output_len = (len / 3 + padding) * 4;
  char *output = calloc(output_len + 1, sizeof(char));
  base64_encode(val, output, len);
  return output;
}
