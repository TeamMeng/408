#include "keyPath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 通过拓扑排序计算出ETV，将拓扑排序的结果倒叙来计算LTV

static int topologicalOrder(AGraph *g, int *ETV, int *LTV) {
  int *inDegree = (int *)malloc(sizeof(int) * g->nodeNum);

  if (inDegree == NULL) {
    printf("inDegree malloc failed!\n");
    return -1;
  }

  for (int i = 0; i < g->nodeNum; ++i) {
    ArcEdge *edge = g->nodes[i].firstEdge;
    while (edge) {
      ++inDegree[edge->no];
      edge = edge->next;
    }
  }

  int *stack = (int *)malloc(sizeof(int) * g->nodeNum);
  int *topOut = (int *)malloc(sizeof(int) * g->nodeNum);
  if (stack == NULL || topOut == NULL) {
    printf("stack or topOut malloc failed!\n");
    free(inDegree);
    return -1;
  }
  int top = -1;

  for (int i = 0; i < g->nodeNum; ++i) {
    if (inDegree[i] == 0) {
      stack[++top] = i;
      break;
    }
  }

  int idx = 0;
  int tmp;
  while (top != -1) {
    tmp = stack[top--];
    topOut[idx++] = tmp;
    ArcEdge *edge = g->nodes[tmp].firstEdge;
    while (edge) {
      --inDegree[edge->no];
      if (inDegree[edge->no] == 0) {
        stack[++top] = edge->no;
      }
      // 更新ETV
      if (ETV[tmp] + edge->weight > ETV[edge->no]) {
        ETV[edge->no] = ETV[tmp] + edge->weight;
      }
      edge = edge->next;
    }
  }

  free(stack);
  free(inDegree);
  if (idx < g->nodeNum) {
    free(topOut);
    return -1;
  }

  for (int i = 0; i < g->nodeNum; ++i) {
    LTV[i] = ETV[tmp];
  }

  int getTopNo;
  while (idx) {
    getTopNo = topOut[--idx];
    ArcEdge *edge = g->nodes[getTopNo].firstEdge;
    while (edge) {
      if (LTV[edge->no] - edge->weight < LTV[getTopNo]) {
        LTV[getTopNo] = LTV[edge->no] - edge->weight;
      }
      edge = edge->next;
    }
  }

  free(topOut);

  return 1;
}

static void showTable(int *table, int n, const char *name) {
  printf("%s: ", name);
  for (int i = 0; i < n; ++i) {
    printf("%d\t", table[i]);
  }
  printf("\n");
}

/* 为了求出AOE网中的关键路径，需要统计4个数据
 * 对于AOE网中顶点有两个时间：
 * ETV：事件最早发生时间
 * LTV：事件最晚发生时间
 * 对于边来说，也有两个时间：
 * ETE: 活动最早发生时间
 * LTE: 活动最晚发生时间
 * 对于所有边来说，它的最早发生时间等于最晚发生时间，这条边就是关键路径
 * */
void keyPath(AGraph *g) {
  int n = sizeof(int) * g->nodeNum;
  int *ETV = (int *)malloc(n);
  int *LTV = (int *)malloc(n);
  if (ETV == NULL || LTV == NULL) {
    printf("ETV or LTV malloc failed!\n");
    return;
  }

  memset(ETV, 0, n);
  memset(LTV, 0, n);

  topologicalOrder(g, ETV, LTV);

  showTable(ETV, g->nodeNum, "ETV");
  showTable(LTV, g->nodeNum, "LTV");

  for (int i = 0; i < g->nodeNum; ++i) {
    ArcEdge *edge = g->nodes[i].firstEdge;
    while (edge) {
      if (ETV[i] == LTV[edge->no] - edge->weight) {
        printf("<%s> --- %d --- <%s>\n", g->nodes[i].show, edge->weight,
               g->nodes[edge->no].show);
      }
      edge = edge->next;
    }
  }

  free(ETV);
  free(LTV);
}
