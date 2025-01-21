#include "linkQueue.h"
#include <stdio.h>
#include <stdlib.h>

// create
LinkQueue *createdLinkQueue() {
  LinkQueue *queue = (LinkQueue *)malloc(sizeof(LinkQueue));

  if (queue == NULL) {
    printf("queue malloc failed!\n");
    return NULL;
  }

  queue->len = 0;
  queue->front = queue->rear = NULL;

  return queue;
}

// release
void releaseLinkQueue(LinkQueue *queue) {
  if (queue) {
    while (queue->front) {
      Node *node = queue->front->next;
      queue->front = node->next;
      free(node);
      queue->len -= 1;
    }
    printf("queue is free, queue len is %d\n", queue->len);
    free(queue);
  }
}

// push
int pushLinkQueue(LinkQueue *queue, Element elem) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    printf("node malloc failed!\n");
    return -1;
  }

  node->elem = elem;

  if (queue->front == NULL) {
    queue->front = queue->rear = node;
  } else {
    queue->rear->next = node;
    queue->rear = node;
  }

  ++queue->len;

  return 0;
}

// pop
int popLinkQueue(LinkQueue *queue, Element *elem) {
  if (queue->front == NULL) {
    printf("Empty!\n");
    return -1;
  }

  *elem = queue->front->elem;

  Node *node = queue->front;
  queue->front = node->next;
  free(node);

  if (queue->front == NULL) {
    queue->rear = NULL;
  }

  --queue->len;

  return 0;
}
