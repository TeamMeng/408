#include "quickFindSet.h"
#include "quickUnionSet.h"
#include <stdio.h>

void test01() {
  int n = 9;
  QuickFindSet *set = createQuickFindSet(n);
  Element data[9];
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
    data[i] = i;
  }

  initQuickFindSet(set, data, n);

  unionQuickFindSet(set, 3, 4);
  unionQuickFindSet(set, 8, 0);
  unionQuickFindSet(set, 2, 3);
  unionQuickFindSet(set, 5, 6);

  if (isSameQuickFindSet(set, 0, 2) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  if (isSameQuickFindSet(set, 2, 4) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  unionQuickFindSet(set, 5, 1);
  unionQuickFindSet(set, 7, 3);
  unionQuickFindSet(set, 1, 6);
  unionQuickFindSet(set, 4, 8);

  if (isSameQuickFindSet(set, 0, 2) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  if (isSameQuickFindSet(set, 2, 4) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  releaseQuickFindSet(set);
}

void test02() {
  int n = 9;
  QuickUnionSet *set = createQuickUnionSet(n);
  Element data[9];
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
    data[i] = i;
  }

  initQuickUnionSet(set, data, n);

  unionQuickUnionSet(set, 3, 4);
  unionQuickUnionSet(set, 8, 0);
  unionQuickUnionSet(set, 2, 3);
  unionQuickUnionSet(set, 5, 6);

  if (isSameQuickUnionSet(set, 0, 2) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  if (isSameQuickUnionSet(set, 2, 4) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  unionQuickUnionSet(set, 5, 1);
  unionQuickUnionSet(set, 7, 3);
  unionQuickUnionSet(set, 1, 6);
  unionQuickUnionSet(set, 4, 8);

  if (isSameQuickUnionSet(set, 0, 2) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  if (isSameQuickUnionSet(set, 2, 4) == 1) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  releaseQuickUnionSet(set);
}

int main(int argc, char *argv[]) {
  test01();
  test02();
  return 0;
}
