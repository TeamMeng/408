#include "linkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create
LinkStack *createdLinkStack() {
  LinkStack *stack = (LinkStack *)malloc(sizeof(LinkStack));

  if (stack == NULL) {
    printf("stack malloc failed!\n");
    return NULL;
  }

  stack->top = NULL;
  stack->len = 0;

  return stack;
}

// release
void releaseLinkStack(LinkStack *stack) {
  if (stack) {
    int cnt = 0;
    while (stack->top) {
      Node *node = stack->top->next;
      stack->top->next = node->next;
      free(node);
      ++cnt;
    }
    printf("stack is free, len is %d\n", cnt);
    free(stack);
  }
}

// push
int pushLinkStack(LinkStack *stack, Element elem) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    printf("node malloc failed!\n");
    return -1;
  }

  node->elem = elem;
  node->next = stack->top;
  stack->top = node;

  ++stack->len;

  return 0;
}

// pop
int popLinkStack(LinkStack *stack, Element *elem) {
  if (!stack->top) {
    printf("Empty!\n");
    return -1;
  }

  *elem = stack->top->elem;

  Node *node = stack->top;
  stack->top = node->next;
  free(node);

  --stack->len;

  return 0;
}
