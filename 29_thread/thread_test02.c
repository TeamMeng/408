#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int value = 0;

void task1(int flag) {
  for (int i = 0; i < 10000000; ++i) {
    value++;
  }
  pthread_exit(NULL);
}

void task2(int flag) {
  for (int i = 0; i < 10000000; ++i) {
    value++;
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2;

  int ret = pthread_create(&tid1, NULL, (void *(*)(void *))task1, (void *)100);
  if (ret) {
    perror("pthread create");
    exit(-1);
  }
  printf("main process: %d create thread: %lu\n", getpid(),
         (unsigned long)tid1);

  ret = pthread_create(&tid2, NULL, (void *(*)(void *))task2, (void *)200);
  if (ret) {
    perror("pthread create");
    exit(-1);
  }
  printf("main process: %d create thread: %lu\n", getpid(),
         (unsigned long)tid2);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("main process value: %d!\n", value);

  return 0;
}
