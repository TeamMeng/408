#ifndef ADJACENT_GRAPH_H
#define ADJACENT_GRAPH_H

#define MaxNodeNum 10
#define INF 1E4

typedef struct arcEdge {
  int no;
  int weight;
  struct arcEdge *next;
} ArcEdge;

typedef struct {
  int no;
  char *show;
  ArcEdge *firstEdge;
} ArcNode;

typedef struct {
  ArcNode *nodes;
  int nodeNum;
  int edgeNum;
  int directed;
} AGraph;

AGraph *createAGraph(int n);

void releaseAGraph(AGraph *g);

void initAGraph(AGraph *g, int num, char *names[], int directed);

void addAGraphEdge(AGraph *g, int x, int y, int w);

#endif
