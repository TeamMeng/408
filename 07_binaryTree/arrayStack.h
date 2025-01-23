#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "binaryTree.h"

// 顺序栈

#define MaxStackSize 20

typedef struct {
  pTreeNode data[MaxStackSize];
  int top;
} ArrayStack;

// create
ArrayStack *createdArrayStack();

// release
void releaseArrayStack(ArrayStack *stack);

// push
int pushArrayStack(ArrayStack *stack, pTreeNode elem);

// pop
int popArrayStack(ArrayStack *stack, pTreeNode *elem);

#endif
