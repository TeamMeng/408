#include "insertSort.h"

int main(int argc, char *argv[]) {
  int n = 100000;
  SortTable *table1 = generateRandomArray(n, 0, n);
  SortTable *table3 = copySortTable(table1);
  SortTable *table5 = copySortTable(table1);

  SortTable *table2 = generateLinearArray(n, 10);
  SortTable *table4 = copySortTable(table2);
  SortTable *table6 = copySortTable(table2);

  testSort("random insert sort v1", insertSortV1, table1);
  testSort("linear insert sort v1", insertSortV1, table2);

  testSort("random insert sort v2", insertSortV2, table3);
  testSort("linear insert sort v2", insertSortV2, table4);

  testSort("random shell insert sort", shellSort, table5);
  testSort("linear shell insert sort", shellSort, table6);

  releaseSortTable(table1);
  releaseSortTable(table2);
  releaseSortTable(table3);
  releaseSortTable(table4);
  releaseSortTable(table5);
  releaseSortTable(table6);
  return 0;
}
