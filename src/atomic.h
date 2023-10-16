#include <pthread.h>

typedef struct {
  int value;
  pthread_mutex_t mutex;
} AtomicInt;

AtomicInt *atomic_init(int value);
int atomic_read(AtomicInt *atomic);
void atomic_set(AtomicInt *atomic, int value);
void atomic_free(AtomicInt *atomic);
