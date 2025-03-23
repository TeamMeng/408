#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int abc = 2;

void task1(int flag) {
  for (int i = 0; i < 5; ++i) {
    sleep(2);
    abc = 100;
  }
  pthread_exit(NULL);
}

void task2(int flag) {
  for (int i = 0; i < 5; ++i) {
    abc = 200;
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2;

  printf("abc: %d\n", abc);
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

  sleep(1);
  printf("abc: %d\n", abc);
  sleep(2);
  printf("abc: %d\n", abc);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("main process exit!\n");

  return 0;
}
