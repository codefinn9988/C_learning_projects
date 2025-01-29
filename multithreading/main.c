/* Learn Multitreading in c
 * */
#include <pthread.h>
#include <stdio.h>
// vargp = variable argument pointer;
void *myThread1();
void *myThread2();
int main() {
  pthread_t thread[2];
  // starting thread
  pthread_create(&thread[0], NULL, myThread1, NULL);
  pthread_create(&thread[1], NULL, myThread2, NULL);
  // waiting for completion
  // The pthread_join() function waits for the thread specified by thread to
  // terminate.;
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  return 0;
}
void *myThread1() {
  int i;
  for (i = 0; i < 5; i++) {
    printf("thread 1 is running \n");
  }
  return NULL;
}

void *myThread2() {
  int i;
  for (i = 0; i < 5; i++) {
    printf("thread 2 is running \n");
  }
  return NULL;
}
