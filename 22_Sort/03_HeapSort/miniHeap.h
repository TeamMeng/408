#ifndef MINI_HEAP_H
#define MINI_HEAP_H

#include "../sortHelper.h"

/* 最小堆结构，使用完全二叉树来存储，使用顺序存储
 * */

typedef struct {
  keyType *data;
  int len;
  int capacity;
} MiniHeap;

MiniHeap *createMiniHeap(int n);

void releaseMiniHeap(MiniHeap *heap);

void insertMiniHeap(MiniHeap *heap, keyType data);

keyType extracMiniHeap(MiniHeap *heap);

#endif
