#include "insertSort.h"

void insertSortV1(SortTable *table) {
  for (int i = 1; i < table->length; ++i) {
    Element e = table->data[i];
    int j = i;
    while (j > 0 && table->data[j - 1].key > e.key) {
      swapElement(&table->data[j], &table->data[j - 1]);
      --j;
    }
    table->data[j] = e;
  }
}

void insertSortV2(SortTable *table) {
  for (int i = 1; i < table->length; ++i) {
    if (table->data[i].key < table->data[i - 1].key) {
      int j = i - 1;
      Element temp = table->data[i];
      while (j > -1 && temp.key < table->data[j].key) {
        table->data[j + 1] = table->data[j];
        --j;
      }
      table->data[j + 1] = temp;
    }
  }
}

void shellSort(SortTable *table) {
  int gap;
  for (gap = table->length / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < table->length; ++i) {
      Element temp = table->data[i];
      int j;
      for (j = i; j >= gap && table->data[j - gap].key > temp.key; j -= gap) {
        swapElement(&table->data[j], &table->data[j - gap]);
      }
      table->data[j] = temp;
    }
  }
}
