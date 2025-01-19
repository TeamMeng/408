#ifndef SEQLIST_H
#define SEQLIST_H

// 动态顺序表，使用顺序存储，数据容量动态增加

typedef int Element;

typedef struct {
  Element *elem; // 顺序表元素空间的首地址
  int len;       // 记录顺序表的元素个数
  int capacity;  // 记录顺序表的容量
} Seqlist;

// 产生容量为capacity个元素的顺序表
Seqlist *createSeqList(int capacity);

// 释放这个顺序表
void releaseSeqList(Seqlist *seq);

// 获取顺序表中某个位置的值
int getSeqList(Seqlist *seq, int pos, Element *elem);

// 查找顺序表中元素的位置
int locateSeqList(Seqlist *seq, Element elem);

// 在pos位置上插入元素
int insertSeqList(Seqlist *seq, int pos, Element elem);

// 显示顺序表中的元素
void showSeqList(Seqlist *seq);

// 从顺序表中删除指定位置处的元素
int deleteSeqList(Seqlist *seq, int pos);

#endif
