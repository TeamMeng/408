#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

static void merge(SortTable *table, int left, int mid, int right) {
  /* 1. 将左右任务的区域进行拷贝，
   * 方便从拷贝的空间里，按照归并的思想，向原空间填入有序的值
   * */
  int n1 = mid - left + 1;
  int n2 = right - mid;
  // 2. 分配aux1和aux2，将空间进行拷贝
  Element *aux1 = (Element *)malloc(sizeof(Element) * n1);
  Element *aux2 = (Element *)malloc(sizeof(Element) * n2);
  if (aux1 == NULL || aux2 == NULL) {
    printf("aux malloc failed!\n");
    return;
  }
  // 3. 将左右任务的子空间进行拷贝
  for (int i = 0; i < n1; ++i) {
    aux1[i] = table->data[i + left];
  }
  for (int i = 0; i < n2; ++i) {
    aux2[i] = table->data[i + mid + 1];
  }
  // 2.将有序的临时的aux1和aux2归并
  int i = 0;
  int j = 0;
  int k = left;
  while (i < n1 && j < n2) {
    if (aux1[i].key <= aux2[j].key) {
      table->data[k] = aux1[i++];
    } else {
      table->data[k] = aux2[j++];
    }
    ++k;
  }
  while (i < n1) {
    table->data[k++] = aux1[i++];
  }
  while (j < n2) {
    table->data[k++] = aux2[j++];
  }
  free(aux1);
  free(aux2);
}

/* 归并任务的访问区域[left..right]
 * */
static void mergeLoop(SortTable *table, int left, int right) {
  if (left >= right) {
    return;
  }
  // 拆分2个小任务
  int mid = (right - left) / 2 + left;
  mergeLoop(table, left, mid);
  mergeLoop(table, mid + 1, right);
  merge(table, left, mid, right);
}

void mergeSort(SortTable *table) { mergeLoop(table, 0, table->length - 1); }
