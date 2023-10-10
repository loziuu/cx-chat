#ifndef WEBSOCKET_H
#define WEBSOCKET_H

char *websocket_decode_key(char *client_key);
// Return the response for the given request.
void websocket_handle(int *confd);

#endif
