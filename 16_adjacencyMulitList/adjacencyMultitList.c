
#include "adjacencyMultitList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AdjacencyMultiList *createMultiList(int n) {
  AdjacencyMultiList *multiList =
      (AdjacencyMultiList *)malloc(sizeof(AdjacencyMultiList));
  multiList->nodes = (MultiListVertex *)malloc(sizeof(MultiListVertex) * n);
  multiList->nodesNum = n;
  multiList->edgeNum = 0;
  return multiList;
}

void initMultiList(AdjacencyMultiList *graph, int n, char **names) {
  for (int i = 0; i < n; ++i) {
    graph->nodes[i].no = i;
    graph->nodes[i].show = names[i];
    graph->nodes[i].firstEdge = NULL;
  }
}

int insertMultiListEdge(AdjacencyMultiList *graph, int a, int b, int w) {
  // 产生这条边
  MultiListEdge *edge = (MultiListEdge *)malloc(sizeof(MultiListEdge));
  edge->weight = w;
  // 处理a节点的连接关系，使用头插法
  edge->iVex = a;
  edge->iNext = graph->nodes[a].firstEdge;
  graph->nodes[a].firstEdge = edge;
  // 处理b节点的连接关系，使用头插法
  edge->jVex = b;
  edge->jNext = graph->nodes[b].firstEdge;
  graph->nodes[b].firstEdge = edge;
  graph->edgeNum++;
  return 0;
}

int deleteMultiListEdge(AdjacencyMultiList *graph, int a, int b) {
  // 找到a编号的前一个节点
  MultiListEdge *aPreEdge = NULL;
  MultiListEdge *aCurEdge = graph->nodes[a].firstEdge;
  while (aCurEdge && !((aCurEdge->iVex == a && aCurEdge->jVex == b) ||
                       (aCurEdge->jVex == a && aCurEdge->iVex == b))) {
    aPreEdge = aCurEdge;
    if (aCurEdge->iVex == a) {
      aCurEdge = aCurEdge->iNext;
    } else {
      aCurEdge = aCurEdge->jNext;
    }
  }
  if (aCurEdge == NULL)
    return -1;
  // 找到b编号的前一个节点
  MultiListEdge *bPreEdge = NULL;
  MultiListEdge *bCurEdge = graph->nodes[b].firstEdge;
  while (bCurEdge && !((bCurEdge->iVex == a && bCurEdge->jVex == b) ||
                       (bCurEdge->jVex == a && bCurEdge->iVex == b))) {
    bPreEdge = bCurEdge;
    if (bCurEdge->iVex == b) {
      bCurEdge = bCurEdge->iNext;
    } else {
      bCurEdge = bCurEdge->jNext;
    }
  }
  if (bCurEdge == NULL)
    return -1;
  // 再删除
  // 先处理a顶点的关系
  if (aPreEdge == NULL) { // a编号的边，是从头节点处开始删除
    if (aCurEdge->iVex == a) {
      graph->nodes[a].firstEdge = aCurEdge->iNext;
    } else {
      graph->nodes[a].firstEdge = aCurEdge->jNext;
    }
  } else { // aCurEdge->iVex == a
    if (aPreEdge->iVex == a) {
      if (aCurEdge->iVex == a)
        aPreEdge->iNext = aCurEdge->iNext;
      else
        aPreEdge->iNext = aCurEdge->jNext;
    } else {
      aPreEdge->jNext = aCurEdge->jNext;
    }
  }
  // 再处理b顶点的关系
  if (bPreEdge == NULL) {
    if (bCurEdge->iVex == b) {
      graph->nodes[b].firstEdge = bCurEdge->iNext;
    } else {
      graph->nodes[b].firstEdge = bCurEdge->jNext;
    }
  } else {
    if (bPreEdge->iVex == b) {
      bPreEdge->iNext = bCurEdge->iNext;
    } else {
      bPreEdge->jNext = bCurEdge->jNext;
    }
  }
  // 释放cur
  free(aCurEdge);
  graph->edgeNum--;
  return 0;
}
