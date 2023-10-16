#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "atomic.h"
#include "linked_list.h"
#include "memutils.h"
#include "websocket.h"

#define NUMBER_OF_CLIENTS 10
#define DEFAULT_PORT 42069

typedef struct {
  int thread_id;
  int *connfd;
} HandlerMetadata;

// TODO: Move it somewhere else I guess...
extern AtomicInt *server_state;

// TODO: Make it atomic (thread safety) obviously
int thread_i = 0;

pthread_t *client_t[NUMBER_OF_CLIENTS];
static pthread_rwlock_t client_mutex = PTHREAD_RWLOCK_INITIALIZER;

HandlerMetadata *metadata_create(int thread_id, int connfd) {
  HandlerMetadata *metadata = malloc(sizeof(HandlerMetadata));
  metadata->thread_id = thread_id;
  metadata->connfd = memutils_copy(&connfd, sizeof(int));
  return metadata;
}

void metadata_free(HandlerMetadata *metadata) {
  free(metadata->connfd);
  free(metadata);
}

// TODO: ADD ROUTING!
void handle_connection(HandlerMetadata *metadata) {
  websocket_handle_new_connection(metadata->connfd);

  shutdown(*metadata->connfd, 2);

  pthread_rwlock_wrlock(&client_mutex);
  thread_i--;
  free(client_t[metadata->thread_id]);
  client_t[metadata->thread_id] = NULL;
  pthread_rwlock_unlock(&client_mutex);

  metadata_free(metadata);
}

void add_client(int connfd) {
  printf("Adding client...");
  pthread_rwlock_wrlock(&client_mutex);

  if (thread_i < NUMBER_OF_CLIENTS && client_t[thread_i] == NULL) {
    // TODO: Freed in handle_connection
    pthread_t *client_thread = malloc(sizeof(pthread_t));
    client_t[thread_i] = client_thread;

    HandlerMetadata *metadata = metadata_create(thread_i, connfd);
    int result = pthread_create(client_thread, NULL, (void *)handle_connection,
                                metadata);
    if (result == 0) {
      printf("Created new thread for client.\n");
      thread_i++;
    } else {
      printf("Error creating thread for client: %d\n", result);
      free(client_thread);
      metadata_free(metadata);
    }
  } else {
    printf("All slots are alread used.\n");
  }

  pthread_rwlock_unlock(&client_mutex);
}

/* TODO: Add thread per connection
 * I guess it's already done to some degree...
 */
void server_run() {
  for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
    client_t[i] = NULL;
  }

  struct sockaddr_in addr;
  int server_socket;

  addr = (struct sockaddr_in){.sin_family = AF_INET,
                              .sin_port = htons(DEFAULT_PORT),
                              .sin_addr.s_addr = INADDR_ANY};

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if ((bind(server_socket, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
    printf("Error binding socket: %d\n", errno);
    return;
  }

  if ((listen(server_socket, NUMBER_OF_CLIENTS)) < 0) {
    printf("Error listening on socket: %d\n", errno);
    return;
  }

  int result;
  // TODO: USE DEFINED CONSTANTS FOR STATE
  while ((result = atomic_read(server_state)) == 0) {
    printf("Server state: %d\n", result);
    printf("Waiting for new clients...\n");
    int connfd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    connfd = accept(server_socket, (struct sockaddr *)&client_addr,
                    &client_addr_len);
    add_client(connfd);
  }
  printf("Shutting down the server...");

  for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
    if (client_t[i] != NULL) {
      pthread_join(*client_t[i], NULL);
    }
  }
  shutdown(server_socket, 2);
}

void send_echo() {
  struct sockaddr_in addr;
  int serverfd;
  int sock;
  addr = (struct sockaddr_in){.sin_family = AF_INET,
                              .sin_port = htons(42069),
                              .sin_addr.s_addr = INADDR_ANY};
  sock = socket(AF_INET, SOCK_STREAM, 0);
  serverfd = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  send(sock, "echo", 4, 0);
  shutdown(serverfd, 2);
}
