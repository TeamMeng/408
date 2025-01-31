#include "quickUnionSet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QuickUnionSet *createQuickUnionSet(int n) {
  QuickUnionSet *set = (QuickUnionSet *)malloc(sizeof(QuickUnionSet));

  if (set == NULL) {
    printf("set malloc failed!\n");
  }

  set->data = (Element *)malloc(sizeof(Element) * n);
  set->parent = (int *)malloc(sizeof(int) * n);
  set->size = (int *)malloc(sizeof(int) * n);
  set->n = n;

  return set;
}

void releaseQuickUnionSet(QuickUnionSet *set) {
  if (set) {
    if (set->data)
      free(set->data);
    if (set->parent)
      free(set->parent);
    if (set->size)
      free(set->size);
    free(set);
  }
}

void initQuickUnionSet(QuickUnionSet *set, Element *data, int n) {
  for (int i = 0; i < n; ++i) {
    set->data[i] = data[i];
    set->parent[i] = i;
    set->size[i] = 1;
  }
}

static int findIndex(QuickUnionSet *set, Element elem) {
  for (int i = 0; i < set->n; ++i) {
    if (set->data[i] == elem) {
      return i;
    }
  }
  return -1;
}

static int findRootIndex(QuickUnionSet *set, Element elem) {
  int index = findIndex(set, elem);

  if (index != -1) {
    while (set->parent[index] != index) {
      index = set->parent[index];
    }
    return index;
  }

  return -1;
}

int isSameQuickUnionSet(QuickUnionSet *set, Element a, Element b) {
  int aRoot = findRootIndex(set, a);
  int bRoot = findRootIndex(set, b);

  if (aRoot == -1 || bRoot == -1) {
    return -1;
  }

  return aRoot == bRoot;
}

/* 1. 找到a和b的根节点
 * 2. 将b的父节点指向a的索引
 * 根据size做优化，谁的元素多，做让另一根接入元素多的根
 * */
int unionQuickUnionSet(QuickUnionSet *set, Element a, Element b) {
  int aRoot = findRootIndex(set, a);
  int bRoot = findRootIndex(set, b);

  if (aRoot == -1 || bRoot == -1) {
    return -1;
  }

  if (aRoot != bRoot) {
    int aSize = set->parent[aRoot];
    int bSize = set->parent[bRoot];

    if (aSize >= bSize) {
      set->parent[bRoot] = aRoot;
      set->size[aRoot] += bSize;
    } else {
      set->parent[aRoot] = bRoot;
      set->size[bRoot] += aSize;
    }
  }

  return 0;
}
