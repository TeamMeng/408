#include "mergeSort.h"

int main(int argc, char *argv[]) {
  int n = 100000;
  SortTable *table = generateRandomArray(n, 0, n);
  testSort("random merge sort", mergeSort, table);
  releaseSortTable(table);
  return 0;
}
