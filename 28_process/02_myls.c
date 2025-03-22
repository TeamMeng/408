#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  int ret;

  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(2);
  }

  switch (pid) {
  // child
  // 替换当前父进程的上下文, 替换成新的进程静态数据区
  case 0:
    ret = execlp("ls", "ls", "-l", NULL);
    if (ret < 0) {
      perror("execlp error");
      exit(-1);
    }
    printf("==============\n");
    break;
  // parent
  default:
    getchar();
    wait(NULL);
    break;
  }

  return 0;
}
