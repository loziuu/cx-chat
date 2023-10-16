#include <pthread.h>
#include <stdlib.h>

#include "atomic.h"

AtomicInt *atomic_init(int value) {
  AtomicInt *atomic = malloc(sizeof(AtomicInt));
  atomic->value = value;
  pthread_mutex_init(&atomic->mutex, NULL);
  return atomic;
}

int atomic_read(AtomicInt *atomic) {
  int val;

  pthread_mutex_lock(&atomic->mutex);
  val = atomic->value;
  pthread_mutex_unlock(&atomic->mutex);

  return val;
}

void atomic_set(AtomicInt *atomic, int value) {
  pthread_mutex_lock(&atomic->mutex);
  atomic->value = value;
  pthread_mutex_unlock(&atomic->mutex);
}

void atomic_free(AtomicInt *atomic) {
  pthread_mutex_lock(&atomic->mutex);
  free(atomic);
}
