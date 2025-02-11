#include "findStr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  StrType str;
  StrType subStr;

  str.str = subStr.str = NULL;

  strAssign(&str, "ABCDABCABCABABCABCDA");
  strAssign(&subStr, "ABCABCD");

  printf("index: %d\n", index_simple(&str, &subStr));

  int *next = (int *)malloc(sizeof(int) * (subStr.length + 1));

  getNext(&subStr, next);
  for (int i = 0; i < subStr.length; ++i) {
    printf("%d\t", next[i]);
  }
  printf("\n");
  printf("index: %d\n", indexKMP(&str, &subStr, next));

  free(next);
  releaseStrType(&str);
  releaseStrType(&subStr);

  return EXIT_SUCCESS;
}
