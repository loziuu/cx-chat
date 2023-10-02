#ifndef BASE64_H
#define BASE64_H

void base64_encode(void *val, char *buf, int len);
void *base64_encode_allocate(void *val, int len);

#endif
