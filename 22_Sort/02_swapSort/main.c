#include "bubbleSort.h"
#include "quickSort.h"

int main(int argc, char *argv[]) {
  int n = 100000;
  SortTable *table1 = generateRandomArray(n, 0, n);
  SortTable *table3 = copySortTable(table1);
  SortTable *table5 = copySortTable(table1);
  SortTable *table7 = copySortTable(table1);
  SortTable *table9 = copySortTable(table1);

  SortTable *table2 = generateLinearArray(n, 10);
  SortTable *table4 = copySortTable(table2);
  SortTable *table6 = copySortTable(table2);
  SortTable *table8 = copySortTable(table2);
  SortTable *table10 = copySortTable(table2);

  testSort("random bubble sort V1", bubbleSortV1, table1);
  testSort("linear bubble sort V1", bubbleSortV1, table2);

  testSort("random bubble sort V2", bubbleSortV2, table3);
  testSort("linear bubble sort V2", bubbleSortV2, table4);

  testSort("random bubble sort V3", bubbleSortV3, table5);
  testSort("linear bubble sort V3", bubbleSortV3, table6);

  testSort("random quick sort V1", quickSortV1, table7);
  testSort("linear quick sort V1", quickSortV1, table8);

  testSort("random quick sort V2", quickSortV2, table9);
  testSort("linear quick sort V2", quickSortV2, table10);

  releaseSortTable(table1);
  releaseSortTable(table2);
  releaseSortTable(table3);
  releaseSortTable(table4);
  releaseSortTable(table5);
  releaseSortTable(table6);
  releaseSortTable(table7);
  releaseSortTable(table8);
  releaseSortTable(table9);
  releaseSortTable(table10);
  return 0;
}
