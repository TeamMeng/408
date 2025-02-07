#include "quickSort.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int partitionDouble(SortTable *table, int startIndex, int endIndex) {
  int pivot = startIndex;
  int left = startIndex;
  int right = endIndex;

  srand(time(NULL) + 1);
  swapElement(&table->data[startIndex],
              &table->data[rand() % (endIndex - startIndex) + startIndex]);

  while (left != right) {
    while (left < right && table->data[right].key > table->data[pivot].key) {
      --right;
    }
    while (left < right && table->data[left].key <= table->data[pivot].key) {
      ++left;
    }

    if (left < right) {
      swapElement(&table->data[right], &table->data[left]);
    }
  }
  swapElement(&table->data[pivot], &table->data[left]);

  return left;
}

static void quickSort1(SortTable *table, int startIndex, int endIndex) {
  if (startIndex >= endIndex) {
    return;
  }

  int pivot = partitionDouble(table, startIndex, endIndex);
  quickSort1(table, startIndex, pivot - 1);
  quickSort1(table, pivot + 1, endIndex);
}

void quickSortV1(SortTable *table) { quickSort1(table, 0, table->length - 1); }

static int partitionSingle(SortTable *table, int startIndex, int endIndex) {
  keyType tmp = table->data[startIndex].key;
  int mark = startIndex;

  for (int i = startIndex + 1; i <= endIndex; ++i) {
    if (table->data[i].key < tmp) {
      swapElement(&table->data[i], &table->data[++mark]);
    }
  }

  swapElement(&table->data[startIndex], &table->data[mark]);

  return mark;
}

static void quickSort2(SortTable *table, int startIndex, int endIndex) {
  if (startIndex >= endIndex) {
    return;
  }

  int pivot = partitionSingle(table, startIndex, endIndex);
  quickSort1(table, startIndex, pivot - 1);
  quickSort1(table, pivot + 1, endIndex);
}

void quickSortV2(SortTable *table) { quickSort2(table, 0, table->length - 1); }
