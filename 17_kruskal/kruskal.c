#include "kruskal.h"
#include <stdlib.h>
#include <string.h>

int initEdgeSet(const MGraph *g, EdgeSet *set) {
  int k = 0;
  for (int i = 0; i < g->nodeNum; ++i) {
    for (int j = i + 1; j < g->nodeNum; ++j) {
      if (g->edges[i][j] > 0) {
        set[k].begin = i;
        set[k].end = j;
        set[k].weight = g->edges[i][j];
        ++k;
      }
    }
  }
  return k;
}

void sortEdgeSet(EdgeSet *set, int num) {
  EdgeSet tmp;
  for (int i = 0; i < num; ++i) {
    for (int j = i + 1; j < num; ++j) {
      if (set[i].weight > set[j].weight) {
        memcpy(&tmp, &set[i], sizeof(EdgeSet));
        memcpy(&set[i], &set[j], sizeof(EdgeSet));
        memcpy(&set[j], &tmp, sizeof(EdgeSet));
      }
    }
  }
}

static int getRoot(const int *uSet, int a) {
  while (a != uSet[a]) {
    a = uSet[a];
  }
  return a;
}

int KruskalMGraph(const MGraph *g, const EdgeSet *set, int num,
                  EdgeSet *result) {
  int *uSet = (int *)malloc(sizeof(int) * g->nodeNum);
  int index = 0;
  int sum = 0;

  if (uSet == NULL) {
    return -1;
  }

  for (int i = 0; i < g->nodeNum; ++i) {
    uSet[i] = i;
  }

  for (int i = 0; (index < (g->nodeNum - 1)) && i < num; ++i) {
    int a = getRoot(uSet, set[i].begin);
    int b = getRoot(uSet, set[i].end);
    if (a != b) {
      uSet[a] = uSet[b];
      result[index].begin = set[i].begin;
      result[index].end = set[i].end;
      result[index++].weight = set[i].weight;
      sum += set[i].weight;
    }
  }

  free(uSet);
  return sum;
}
