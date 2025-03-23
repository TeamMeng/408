#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void task1(int flag) {
  for (int i = 0; i < 5; ++i) {
    printf("task running: %d\n", flag);
    sleep(1);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t tid;

  int ret = pthread_create(&tid, NULL, (void *(*)(void *))task1, (void *)100);
  if (ret) {
    perror("pthread create");
    exit(-1);
  }
  printf("main process: %d create thread: %lu\n", getpid(), (long unsigned)tid);

  return 0;
}
