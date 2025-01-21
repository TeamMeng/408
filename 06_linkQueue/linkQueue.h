#ifndef LINKQUEUE_H
#define LINKQUEUE_H

typedef int Element;

typedef struct Node {
  struct Node *next;
  Element elem;
} Node;

typedef struct {
  struct Node *front;
  struct Node *rear;
  int len;
} LinkQueue;

// create
LinkQueue *createdLinkQueue();

// release
void releaseLinkQueue(LinkQueue *queue);

// push
int pushLinkQueue(LinkQueue *queue, Element elem);

// pop
int popLinkQueue(LinkQueue *queue, Element *elem);

#endif
