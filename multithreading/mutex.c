/* mutual exclusion
 * Dijkstra paper:  https://dl.acm.org/doi/pdf/10.1145/365559.365617
 */

#include <pthread.h>
#include <stdio.h>
pthread_mutex_t lock;
int sharedData = 0;
void *increment(void *args) {
  pthread_mutex_lock(&lock);

  // critical section begin
  sharedData++;
  printf("Thread %lu incremented sharedData to %d\n", (long)args, sharedData);
  // critical section end

  pthread_mutex_unlock(&lock);
  return NULL;
}
int main() {
  ;
  const int numberOfThreads = 5;
  pthread_t thread[numberOfThreads];
  // initialize the mutux
  pthread_mutex_init(&lock, NULL);

  // create the thread
  for (long i = 0; i < numberOfThreads; i++) {
    if (pthread_create(&thread[i], NULL, increment, (void *)i) != 0) {
      printf("Failed to create Thread");
      return 1;
    }
  }

  // joining the thread
  for (int i = 0; i < numberOfThreads; i++) {
    if (pthread_join(thread[i], NULL) != 0) {
      printf("Failed to join thread");
      return 1;
    }
  }
  // destroy the mutux for freeing resources
  pthread_mutex_destroy(&lock);
  printf("Final value of sharedData %d\n", sharedData);
  return 0;
}
/*
 * without mutex
 * Thread 2 incremented sharedData to 1
 * Thread 0 incremented sharedData to 2
 * Thread 1 incremented sharedData to 3
 * Thread 3 incremented sharedData to 4
 * Thread 4 incremented sharedData to 5
 * Final value of sharedData 5
 *
 * using mutex
 * Thread 0 incremented sharedData to 1
 * Thread 1 incremented sharedData to 2
 * Thread 2 incremented sharedData to 3
 * Thread 3 incremented sharedData to 4
 * Thread 4 incremented sharedData to 5
 * Final value of sharedData 5
 */
