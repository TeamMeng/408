#include "linkStack.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  LinkStack *stack = createdLinkStack();

  for (int i = 1; i <= 5; ++i) {
    pushLinkStack(stack, i);
  }

  Element elem;
  for (int i = 1; i <= 5; ++i) {
    popLinkStack(stack, &elem);
    printf("%d ", elem);
  }

  printf("\n");

  // empty
  popLinkStack(stack, &elem);

  releaseLinkStack(stack);

  return 0;
}
