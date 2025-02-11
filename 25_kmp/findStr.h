#ifndef FIND_STR_H
#define FIND_STR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *str;
  int length;
} StrType;

int strAssign(StrType *str, const char *ch);

void releaseStrType(StrType *str);

int index_simple(const StrType *str, const StrType *subStr);

int indexKMP(const StrType *str, const StrType *subStr, const int *next);

void getNext(const StrType *subStr, int *next);

#endif
