#include "arrayQueue.h"
#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create
ArrayQueue *createdArrayQueue() {
  ArrayQueue *queue = (ArrayQueue *)malloc(sizeof(ArrayQueue));

  if (queue == NULL) {
    printf("queue malloc failed!\n");
    return NULL;
  }

  queue->rear = queue->front = 0;

  return queue;
}

// release
void releaseArrayQueue(ArrayQueue *queue) {
  if (queue) {
    free(queue);
  }
}

// push
int pushArrayQueue(ArrayQueue *queue, pTreeNode elem) {
  if ((queue->front + 1) % MaxSize == queue->rear) {
    printf("Full!\n");
    return -1;
  }

  queue->data[queue->front] = elem;
  queue->front = (queue->front + 1) % MaxSize;

  return 0;
}

// pop
int popArrayQueue(ArrayQueue *queue, pTreeNode *elem) {
  if (queue->front == queue->rear) {
    printf("Empty!\n");
    return -1;
  }

  *elem = queue->data[queue->rear];
  queue->rear = (queue->rear + 1) % MaxSize;

  return 0;
}
