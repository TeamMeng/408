#ifndef QUICK_UNION_SET_H
#define QUICK_UNION_SET_H

#include "base.h"

/* 每个元素只保存他的父元素的编号，通过不断找父元素，最终找到根编号
 * find: 两个元素的根一样
 * union: a元素的根和b元素的根 进行合并
 * */

typedef struct {
  Element *data;
  int n;
  // 每个元素只知道他的父节点，通过父节点不断前找根节点
  int *parent;
  // 根节点位置存放这个集合的个数
  int *size;
} QuickUnionSet;

QuickUnionSet *createQuickUnionSet(int n);

void releaseQuickUnionSet(QuickUnionSet *set);

void initQuickUnionSet(QuickUnionSet *set, Element *data, int n);

int isSameQuickUnionSet(QuickUnionSet *set, Element a, Element b);

int unionQuickUnionSet(QuickUnionSet *set, Element a, Element b);

#endif
