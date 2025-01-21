#include "arrayQueue.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  ArrayQueue *q = createdArrayQueue();
  for (int i = 1; i < MaxSize; ++i) {
    pushArrayQueue(q, i);
  }

  // full
  pushArrayQueue(q, 5);

  Element elem;
  for (int i = 1; i < MaxSize; ++i) {
    popArrayQueue(q, &elem);
    printf("%d ", elem);
  }
  printf("\n");

  // empty
  popArrayQueue(q, &elem);

  releaseArrayQueue(q);

  return 0;
}
