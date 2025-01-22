#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

typedef int Element;

#define MaxSize 5

typedef struct {
  Element data[MaxSize];
  int front;
  int rear;
} ArrayQueue;

// create
ArrayQueue *createdArrayQueue();

// release
void releaseArrayQueue(ArrayQueue *queue);

// push
int pushArrayQueue(ArrayQueue *queue, Element elem);

// pop
int popArrayQueue(ArrayQueue *queue, Element *elem);

#endif
