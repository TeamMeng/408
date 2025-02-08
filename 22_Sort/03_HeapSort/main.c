#include "heapSort.h"
#include "miniHeap.h"
#include <stdio.h>

void test01() {
  int data[] = {9, 3, 7, 6, 5, 1, 10, 2};
  int n = sizeof(data) / sizeof(data[0]);
  MiniHeap *heap = createMiniHeap(n);

  if (heap == NULL) {
    return;
  }

  for (int i = 0; i < n; ++i) {
    insertMiniHeap(heap, data[i]);
  }

  for (int i = 1; i <= heap->len; ++i) {
    printf("%d\t", heap->data[i]);
  }
  printf("\n");

  for (int i = 0; i < n; ++i) {
    printf("%d\t", extracMiniHeap(heap));
  }

  releaseMiniHeap(heap);
}

void test02() {
  int n = 100000;
  SortTable *table = generateRandomArray(n, 0, n);
  testSort("Mini heap Sort", miniHeapSort, table);

  releaseSortTable(table);
}

int main(int argc, char *argv[]) {
  test01();
  test02();
  return 0;
}
