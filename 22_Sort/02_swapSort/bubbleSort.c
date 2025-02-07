#include "bubbleSort.h"

void bubbleSortV1(SortTable *table) {
  for (int i = 0; i < table->length; ++i) {
    for (int j = 0; j < table->length - i - 1; ++j) {
      if (table->data[j].key > table->data[j + 1].key) {
        swapElement(&table->data[j], &table->data[j + 1]);
      }
    }
  }
}

void bubbleSortV2(SortTable *table) {
  for (int i = 0; i < table->length; ++i) {
    int flag = 1;
    for (int j = 0; j < table->length - i - 1; ++j) {
      if (table->data[j].key > table->data[j + 1].key) {
        swapElement(&table->data[j], &table->data[j + 1]);
        flag = 0;
      }
    }

    if (flag) {
      break;
    }
  }
}

/* 引入newIndex，标记最后一次交换的位置，下次冒泡排序是，
 * 只需要遍历到这个newIndex + 1位置
 * */
void bubbleSortV3(SortTable *table) {
  int newIndex;
  int n = table->length;
  do {
    newIndex = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (table->data[i].key > table->data[i + 1].key) {
        swapElement(&table->data[i], &table->data[i + 1]);
        newIndex = i + 1;
      }
    }
    n = newIndex;
  } while (newIndex > 0);
}
