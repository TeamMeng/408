#ifndef QUICK_FIND_SET_H
#define QUICK_FIND_SET_H

#include "base.h"

/* 每一个元素都存有一个编号，只要编号一样，就代表一个集团的人
 * 合并时，就是把另外一个团队的人的老大为这个团队的老大
 */

typedef struct {
  Element *data; // 存放的具体数据，利用索引来建立数据的关系
  int n;         // 并查集的元素个数
  int *groupID;  // 每个元素的编号
} QuickFindSet;

QuickFindSet *createQuickFindSet(int n);

void releaseQuickFindSet(QuickFindSet *set);

void initQuickFindSet(QuickFindSet *set, const Element *data, int n);

int isSameQuickFindSet(QuickFindSet *set, Element a, Element b);

void unionQuickFindSet(QuickFindSet *set, Element a, Element b);

#endif
