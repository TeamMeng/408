#include "heapSort.h"
#include "miniHeap.h"

void miniHeapSort(SortTable *table) {
  MiniHeap *heap = createMiniHeap(table->length);
  for (int i = 0; i < table->length; ++i) {
    insertMiniHeap(heap, table->data[i].key);
  }
  for (int i = 0; i < table->length; ++i) {
    table->data[i].key = extracMiniHeap(heap);
  }
  releaseMiniHeap(heap);
}
