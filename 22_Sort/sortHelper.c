#include "sortHelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swapElement(Element *a, Element *b) {
  Element tmp;
  memcpy(&tmp, a, sizeof(Element));
  memcpy(a, b, sizeof(Element));
  memcpy(b, &tmp, sizeof(Element));
}

// 产生随机数范围[low, high]
SortTable *generateRandomArray(int n, int low, int high) {
  SortTable *table = (SortTable *)malloc(sizeof(SortTable));

  if (table == NULL) {
    printf("table malloc failed!\n");
    return NULL;
  }

  table->length = n;
  table->data = (Element *)malloc(sizeof(Element) * n);
  if (table->data == NULL) {
    free(table);
    printf("data malloc failed!\n");
    return NULL;
  }

  srand(time(NULL) + 1);
  for (int i = 0; i < n; ++i) {
    table->data[i].key = (rand() % (high - low + 1) + low);
    table->data[i].data = NULL;
  }

  return table;
}

// 参数顺序空间，随机交换swapTimes次
SortTable *generateLinearArray(int n, int swapTimes) {
  SortTable *table = (SortTable *)malloc(sizeof(SortTable));
  if (table == NULL) {
    printf("table malloc failed!\n");
    return NULL;
  }
  table->length = n;
  table->data = (Element *)malloc(sizeof(Element) * n);
  if (table->data == NULL) {
    free(table);
    printf("data malloc failed!\n");
    return NULL;
  }

  for (int i = 0; i < n; ++i) {
    table->data[i].key = i;
    table->data[i].data = NULL;
  }

  srand(time(NULL) + 2);
  for (int i = 0; i < swapTimes; ++i) {
    int pos = rand() % n;
    int idx = rand() % n;
    swapElement(&table->data[pos], &table->data[idx]);
  }

  return table;
}

// 拷贝和old一样值的排序顺序表
SortTable *copySortTable(SortTable *old) {
  SortTable *table = (SortTable *)malloc(sizeof(SortTable));
  if (table == NULL) {
    printf("table malloc failed!\n");
    return NULL;
  }
  table->length = old->length;
  table->data = (Element *)malloc(sizeof(Element) * old->length);
  if (table->data == NULL) {
    free(table);
    printf("data malloc failed!\n");
    return NULL;
  }

  for (int i = 0; i < old->length; ++i) {
    table->data[i].key = old->data[i].key;
    table->data[i].data = old->data[i].data;
  }

  return table;
}

void releaseSortTable(SortTable *table) {
  if (table) {
    if (table->data) {
      free(table->data);
    }
    free(table);
  }
}

// 检查排序表里的数据，是否从小到大排序
static enum sortStatus checkData(SortTable *table) {
  for (int i = 0; i < table->length - 1; ++i) {
    if (table->data[i].key > table->data[i + 1].key) {
      printf("Check Sort Data Failed: %d : %d\n", table->data[i].key,
             table->data[i + 1].key);
      return failed;
    }
  }
  return success;
}

// 测试sortName的排序算法
void testSort(const char *sortName, sortHandler sort, SortTable *table) {
  clock_t start = clock();
  sort(table);
  clock_t end = clock();
  if (checkData(table) == failed) {
    printf("%s failed!\n", sortName);
    return;
  }
  printf("%s cost time: %fs.\n", sortName,
         (double)(end - start) / CLOCKS_PER_SEC);
}
