#include "server.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Mutex for server state
static pthread_rwlock_t server_mutex;

/*
 * 0 - running
 * 1 - shutting down
 * 2 - shutdown
 */
int server_state = 2;

void shutdown_server() {
  pthread_rwlock_wrlock(&server_mutex);
  server_state = 1;
  pthread_rwlock_unlock(&server_mutex);
}

int main() {
  pthread_t server_thread;

  int result = pthread_create(&server_thread, NULL, (void *) server_run, NULL);
  if (result != 0) {
    printf("Error creating server thread: %d\n", result);
    exit(1);
  }

  printf("Starting server...\n");
  while (1) {
    printf("Server > ");
    char *input = malloc(100);
    scanf("%s", input); 
    printf("\n");
    if (strcmp(input, "exit") == 0) {
      printf("Shutting down server...\n");
      shutdown_server();
      break;
    }
  }

  pthread_join(server_thread, NULL);
  pthread_rwlock_destroy(&server_mutex);
  server_state = 2;
  printf("Server shut down.\n");
  return 0;
}
