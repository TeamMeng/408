#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include "binaryTree.h"

#define MaxSize 20

typedef struct {
  pTreeNode data[MaxSize];
  int front;
  int rear;
} ArrayQueue;

// create
ArrayQueue *createdArrayQueue();

// release
void releaseArrayQueue(ArrayQueue *queue);

// push
int pushArrayQueue(ArrayQueue *queue, pTreeNode elem);

// pop
int popArrayQueue(ArrayQueue *queue, pTreeNode *elem);

#endif
