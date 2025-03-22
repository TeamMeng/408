#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int abc = 100;

void child() {
  abc = 200;
  printf("in child procese %d...%d\n", getpid(), abc);
  sleep(2);
}

void parent() {
  sleep(1);
  printf("in parent procese %d...%d\n", getpid(), abc);
}

int main(int argc, char *argv[]) {
  printf("fork test...\n");
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(2);
  }

  switch (pid) {
  // child
  case 0:
    child();
    break;
  // parent
  default:
    parent();
    break;
  }

  return 0;
}
