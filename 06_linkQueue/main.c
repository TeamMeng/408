#include "linkQueue.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  LinkQueue *q = createdLinkQueue();
  for (int i = 1; i <= 5; ++i) {
    pushLinkQueue(q, i);
  }

  Element elem;
  for (int i = 1; i <= 5; ++i) {
    popLinkQueue(q, &elem);
    printf("%d ", elem);
  }
  printf("\n");

  // empty
  popLinkQueue(q, &elem);

  releaseLinkQueue(q);

  return 0;
}
