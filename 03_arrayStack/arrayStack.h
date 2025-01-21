#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

// 顺序栈
typedef int Element;

#define MaxStackSize 5

typedef struct {
  Element data[MaxStackSize];
  int top;
} ArrayStack;

// create
ArrayStack *createdArrayStack();

// release
void releaseArrayStack(ArrayStack *stack);

// push
int pushArrayStack(ArrayStack *stack, Element elem);

// pop
int popArrayStack(ArrayStack *stack, Element *elem);

#endif
