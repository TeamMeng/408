#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int value1 = 0;
int value2 = 0;

void task1(int flag) {
  while (1) {
    value1++;
    value2++;
  }
  pthread_exit(NULL);
}

void task2(int flag) {
  while (1) {
    if (value1 != value2) {
      printf("value1: %d, value2: %d\n", value1, value2);
    }
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

  printf("main process exit!\n");

  return 0;
}
