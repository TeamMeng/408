#ifndef SORT_HELPER_H
#define SORT_HELPER_H

typedef int keyType;

typedef struct {
  keyType key;
  void *data;
} Element;

typedef struct {
  Element *data;
  int length;
} SortTable;

enum sortStatus { success, failed };

void swapElement(Element *a, Element *b);

// 产生随机数范围[low, high]
SortTable *generateRandomArray(int n, int low, int high);

// 参数顺序空间，随机交换swapTimes次
SortTable *generateLinearArray(int n, int swapTimes);

// 拷贝和old一样值的排序顺序表
SortTable *copySortTable(SortTable *old);

void releaseSortTable(SortTable *table);

// 排序算法函数的别名
typedef void (*sortHandler)(SortTable *);

// 测试sortName的排序算法
void testSort(const char *sortName, sortHandler sort, SortTable *table);

#endif
