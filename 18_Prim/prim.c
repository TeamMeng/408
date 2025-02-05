#include "prim.h"
#include <stdio.h>
#include <stdlib.h>

int PrimMGraph(MGraph *g, int startV, EdgeSet *result) {
  int *cost = (int *)malloc(sizeof(int) * g->nodeNum);
  int *mark = (int *)malloc(sizeof(int) * g->nodeNum);
  int *visit = (int *)malloc(sizeof(int) * g->nodeNum);

  if (cost == NULL || mark == NULL || visit == NULL) {
    return -1;
  }

  int sum = 0;

  // 初始化
  for (int i = 0; i < g->nodeNum; ++i) {
    cost[i] = g->edges[startV][i];
    mark[i] = 0;
    if (cost[i] < INF) {
      visit[i] = startV;
    } else {
      visit[i] = -1;
    }
  }

  mark[startV] = 1;

  // 激活节点，添加到边集
  for (int i = 0; i < g->nodeNum - 1; ++i) {
    // 从权值代价数组里，找到未激活节点的最小值和当前节点的编号
    int min = INF;
    int idx = -1;

    for (int j = 0; j < g->nodeNum; ++j) {
      if (mark[j] == 0 && cost[j] < min) {
        min = cost[j];
        idx = j;
      }
    }

    mark[idx] = 1;
    result[i].begin = visit[idx];
    result[i].end = idx;
    result[i].weight = min;
    sum += min;

    for (int j = 0; j < g->nodeNum; ++j) {
      if (mark[j] == 0 && g->edges[idx][j] < cost[j]) {
        cost[j] = g->edges[idx][j];
        visit[j] = idx;
      }
    }
  }

  free(cost);
  free(mark);
  free(visit);

  return sum;
}
