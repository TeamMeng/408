#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 孤儿
void childProcess() {
  sleep(1);
  printf("pid: %d, ppid: %d\n", getpid(), getppid());
}

int main(int argc, char const *argv[]) {
  printf("fork test...\n");
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(2);
  } else if (pid == 0) {
    childProcess();
  } else {
    exit(0);
  }

  return 0;
}

// int main(int argc, char const *argv[]) {
//   while (1) {
//     printf("========\n");
//   }
//   return 0;
// }
