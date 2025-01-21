#ifndef LINKSTACK_H
#define LINKSTACK_H
// 链式栈
typedef int Element;

typedef struct Node {
  Element elem;
  struct Node *next;
} Node;

typedef struct {
  Node *top;
  int len;
} LinkStack;

// create
LinkStack *createdLinkStack();

// release
void releaseLinkStack(LinkStack *stack);

// push
int pushLinkStack(LinkStack *stack, Element elem);

// pop
int popLinkStack(LinkStack *stack, Element *elem);

#endif
