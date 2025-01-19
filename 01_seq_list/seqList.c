#include "seqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Seqlist *createSeqList(int capacity) {
  Seqlist *seq = (Seqlist *)malloc(sizeof(Seqlist));

  if (seq == NULL) {
    printf("SeqList malloc failed!\n");
    return NULL;
  }

  Element *elem = (Element *)malloc(sizeof(Element) * capacity);
  if (elem == NULL) {
    printf("Elem malloc failed!\n");
    free(seq);
    return NULL;
  }
  // 初始化顺序表中的每个元素
  for (int i = 0; i < capacity; ++i) {
    elem[i] = 0;
  }

  seq->elem = elem;
  seq->len = 0;
  seq->capacity = capacity;

  return seq;
}

void releaseSeqList(Seqlist *seq) {
  if (seq) {
    if (seq->elem) {
      free(seq->elem);
    }
    free(seq);
  }
}

// [1 2 . seq->len] 用户访问范围
int getSeqList(Seqlist *seq, int pos, Element *elem) {
  if (pos < 1 || pos > seq->len) {
    printf("pos invalid!\n");
    return -1;
  }

  *elem = seq->elem[pos - 1];
  return 0;
}

int locateSeqList(Seqlist *seq, Element elem) {
  for (int i = 0; i < seq->len; ++i) {
    if (seq->elem[i] == elem) {
      return i + 1;
    }
  }
  return 0;
}

int insertSeqList(Seqlist *seq, int pos, Element elem) {
  if (pos < 1 || pos > seq->len + 1) {
    printf("pos invalid!\n");
    return -1;
  }

  // 是否扩容
  if (seq->len + 1 > seq->capacity) {
    printf("enlarger!\n");
    Element *tmp = (Element *)malloc(sizeof(Element) * seq->capacity * 2);
    if (tmp == NULL) {
      printf("malloc failed!\n");
      return -1;
    }

    for (int i = 0; i < seq->len; ++i) {
      tmp[i] = seq->elem[i];
    }
    seq->capacity *= 2;
    free(seq->elem);
    seq->elem = tmp;
  }

  // 将pos位置后的元素往前移,从seq->len到pos位置
  for (int i = seq->len; i >= pos; --i) {
    seq->elem[i] = seq->elem[i - 1];
  }
  seq->elem[pos - 1] = elem;
  ++seq->len;

  return 0;
}

void showSeqList(Seqlist *seq) {
  for (int i = 0; i < seq->len; ++i) {
    printf("%d ", seq->elem[i]);
  }
  printf("\n");
  printf("len: %d\n\n", seq->len);
}

int deleteSeqList(Seqlist *seq, int pos) {
  if (pos < 1 || pos > seq->len) {
    printf("pos invalid!\n");
    return -1;
  }

  // 从pos开始到最后的位置处，往前赋值
  for (int i = pos; i < seq->len; ++i) {
    seq->elem[i - 1] = seq->elem[i];
  }

  --seq->len;

  return 0;
}
