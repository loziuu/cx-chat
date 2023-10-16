#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atomic.h"
#include "server.h"
#include "web.h"

/*
 * 0 - running
 * 1 - shutting down
 * 2 - shutdown
 */
AtomicInt *server_state;

pthread_t server_thread;
pthread_t web_thread;

void shutdown_server() {
  atomic_set(server_state, 1);
  send_echo();
}

int main() {
  server_state = atomic_init(0);
  int result;

  if ((result =
           pthread_create(&web_thread, NULL, (void *)run_web, NULL) != 0)) {
    printf("Error creating web server thread: %d\n", result);
    exit(1);
  }

  result = pthread_create(&server_thread, NULL, (void *)server_run, NULL);
  if (result != 0) {
    printf("Error creating server thread: %d\n", result);
    exit(1);
  }

  printf("Starting server...");
  char *input = malloc(100);
  while (1) {
    printf("Server > ");
    scanf("%s", input);
    printf("\n");
    if (strcmp(input, "exit") == 0) {
      shutdown_server();
      break;
    }
  }
  free(input);

  pthread_join(web_thread, NULL);
  pthread_join(server_thread, NULL);
  atomic_set(server_state, 2);
  atomic_free(server_state);
  printf("Server shut down.\n");
  return 0;
}
