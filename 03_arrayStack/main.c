#include "arrayStack.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  ArrayStack *stack = createdArrayStack();

  for (int i = 1; i <= MaxStackSize; ++i) {
    pushArrayStack(stack, i);
  }

  // full
  pushArrayStack(stack, 6);

  Element elem;
  for (int i = 1; i <= MaxStackSize; ++i) {
    popArrayStack(stack, &elem);
    printf("%d ", elem);
  }
  printf("\n");

  // empty
  popArrayStack(stack, &elem);

  releaseArrayStack(stack);

  return 0;
}
