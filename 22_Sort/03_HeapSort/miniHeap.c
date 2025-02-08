#include "miniHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 满足节点的访问行为 [i/2, i, 2i, 2i + 1]
 * 根节点从1号索引开始存储
 * */
MiniHeap *createMiniHeap(int n) {
  MiniHeap *heap = (MiniHeap *)malloc(sizeof(MiniHeap));
  if (heap == NULL) {
    printf("heap malloc failed!\n");
    return NULL;
  }

  keyType *data = (keyType *)malloc(sizeof(keyType) * (n + 1));
  if (data == NULL) {
    free(heap);
    printf("data malloc failed!\n");
    return NULL;
  }

  memset(data, 0, sizeof(keyType) + (n + 1));

  heap->data = data;
  heap->len = 0; // ++len
  heap->capacity = n;

  return heap;
}

void releaseMiniHeap(MiniHeap *heap) {
  if (heap) {
    if (heap->data) {
      free(heap->data);
    }
    free(heap);
  }
}

static void shiftUp(MiniHeap *heap, int idx) {
  while (idx > 1 && heap->data[idx / 2] > heap->data[idx]) {
    keyType tmp = heap->data[idx / 2];
    heap->data[idx / 2] = heap->data[idx];
    heap->data[idx] = tmp;

    idx /= 2;
  }
}

static void shiftDown(MiniHeap *heap, int idx) {
  while (2 * idx <= heap->len) {
    int i = idx * 2;
    if (i + 1 <= heap->len && heap->data[i + 1] < heap->data[i]) {
      i += 1;
    }
    if (heap->data[idx] <= heap->data[i]) {
      break;
    }
    keyType tmp = heap->data[idx];
    heap->data[idx] = heap->data[i];
    heap->data[i] = tmp;
    idx = i;
  }
}

void insertMiniHeap(MiniHeap *heap, keyType data) {
  if (heap->len + 1 > heap->capacity) {
    printf("MiniHeap space full!\n");
    return;
  }

  heap->data[++heap->len] = data;
  shiftUp(heap, heap->len);
}

keyType extracMiniHeap(MiniHeap *heap) {
  if (heap->len <= 0) {
    printf("No data!\n");
    return -1;
  }

  keyType ret = heap->data[1];
  heap->data[1] = heap->data[heap->len--];
  shiftDown(heap, 1);
  return ret;
}
