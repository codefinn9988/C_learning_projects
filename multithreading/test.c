#include <pthread.h>
#include <stdio.h>

void *threadFunction(void *arg) {
  printf("Thread %d is running.\n", *(int *)arg);
  return NULL;
}

int main() {
  pthread_t threads[4];
  int threadArgs[4];

  for (int i = 0; i < 4; i++) {
    threadArgs[i] = i;
    pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

