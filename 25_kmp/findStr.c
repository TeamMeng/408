#include "findStr.h"
#include <stdio.h>
#include <stdlib.h>

int strAssign(StrType *str, const char *ch) {
  if (str->str) {
    free(str->str);
  }

  int len = 0;
  while (ch[len]) {
    ++len;
  }

  if (len == 0) {
    str->str = NULL;
    str->length = 0;
  } else {
    str->str = (char *)malloc(sizeof(char) * (len + 2));
    if (str->str == NULL) {
      printf("str malloc failed!\n");
      return -1;
    }

    for (int i = 0; i <= len; ++i) {
      str->str[i + 1] = ch[i];
    }

    str->length = len;
  }

  return 0;
}

void releaseStrType(StrType *str) {
  if (str) {
    if (str->str) {
      free(str->str);
    }
  }
}

int index_simple(const StrType *str, const StrType *subStr) {
  int i = 1;
  int j = 1;
  int k = i;

  while (i <= str->length && j <= subStr->length) {
    if (str->str[i] == subStr->str[j]) {
      ++i;
      ++j;
    } else {
      i = ++k;
      j = 1;
    }
  }

  if (j > subStr->length) {
    return k;
  }

  return 0;
}

void getNext(const StrType *subStr, int *next) {
  int i = 1, j = 0;
  next[1] = 0;
  while (i < subStr->length) {
    if (j == 0 || subStr->str[i] == subStr->str[j]) {
      next[++i] = ++j;
    } else {
      j = next[j];
    }
  }
}

int indexKMP(const StrType *str, const StrType *subStr, const int *next) {
  int i = 1;
  int j = 1;

  while (i <= str->length && j <= subStr->length) {
    if (j == 0 || str->str[i] == subStr->str[j]) {
      ++i;
      ++j;
    } else {
      j = next[j];
    }
  }

  if (j > subStr->length) {
    return i - subStr->length;
  }

  return 0;
}
