#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#define MaxNodeNum 10
#define INF 1E4

typedef struct {
  int no;     // 顶点编号
  char *show; // 显示
} MaxtrixVertex;

typedef int MatrixEdge;

typedef struct {
  MaxtrixVertex vex[MaxNodeNum];
  int nodeNum;
  MatrixEdge edges[MaxNodeNum][MaxNodeNum];
  int edgeNum;
  int directed;
} MGraph;

void initMGraph(MGraph *g, int num, char *names[], int directed, int edgeValue);

void addMGraphEdge(MGraph *g, int x, int y, int w);

void visitMGraphNode(MaxtrixVertex *node);

void DFSMGraphTravel(MGraph *g, int v);

void clearMGraphVisit();

void BFSMGraphTravel(MGraph *g, int v);

#endif
