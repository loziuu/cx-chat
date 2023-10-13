#ifndef WEBSOCKET_H
#define WEBSOCKET_H

char *websocket_decode_key(char *client_key);
void websocket_handle(int *confd);
void websocket_handle_new_connection(int *connfd);

#endif
