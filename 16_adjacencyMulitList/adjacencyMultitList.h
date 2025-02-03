#ifndef ADJACENCY_MULIT_LIST_H
#define ADJACENCY_MULIT_LIST_H

// 邻接多重表，使用于无向图，边的删除操作

typedef struct amlEdge {
  int iVex;
  struct amlEdge *iNext;
  int jVex;
  struct amlEdge *jNext;
  int weight;
} MultiListEdge;

typedef struct {
  int no;
  char *show;
  MultiListEdge *firstEdge;
} MultiListVertex;

typedef struct {
  MultiListVertex *nodes;
  int nodesNum;
  int edgeNum;
} AdjacencyMultiList;

AdjacencyMultiList *createMultiList(int n);

void releaseMultiList(AdjacencyMultiList *g);

void initMultiList(AdjacencyMultiList *g, int num, char *names[]);

int insertMultiListEdge(AdjacencyMultiList *g, int a, int b, int w);

int deleteMultiListEdge(AdjacencyMultiList *g, int a, int b);

#endif
