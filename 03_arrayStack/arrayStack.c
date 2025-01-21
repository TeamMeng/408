#include "arrayStack.h"
#include <stdio.h>
#include <stdlib.h>

ArrayStack *createdArrayStack() {
  ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));

  if (stack == NULL) {
    printf("stack malloc failed!\n");
    return NULL;
  }

  stack->top = -1;

  return stack;
}

// release
void releaseArrayStack(ArrayStack *stack) {
  if (stack) {
    free(stack);
  }
}

// push
int pushArrayStack(ArrayStack *stack, Element elem) {
  if (stack->top + 1 == MaxStackSize) {
    printf("OverFlow\n");
    return -1;
  }

  stack->data[++stack->top] = elem;

  return 0;
}

// pop
int popArrayStack(ArrayStack *stack, Element *elem) {
  if (stack->top == -1) {
    printf("Empty\n");
    return -1;
  }

  *elem = stack->data[stack->top--];
  return 0;
}
