#ifndef CROSS_LINK_GRAPH_H
#define CROSS_LINK_GRAPH_H

typedef struct arcBox {
  int tailVertex;          // 弧尾编号，出度的信息
  struct arcBox *tailNext; // 下一个弧尾，入度的信息
  int headVertex;          // 弧头编号，入度的信息
  struct arcBox *headNext; // 下一个弧头，下一个入度
  int weight;              // 弧的权重
} ArcBox;

typedef struct {
  int no;
  const char *show;
  ArcBox *firstIn;  // 该节点的入度
  ArcBox *firstOut; // 该节点的出度
} CrossVertex;

typedef struct {
  CrossVertex *nodes;
  int nodeNum;
  int edgeNum;
} CrossGraph;

CrossGraph *createCrossGraph(int n);

void initCrossGraph(CrossGraph *g, int num, char *names[]);

void releaseCorssGraph(CrossGraph *g);

void addCrossArc(CrossGraph *g, int tail, int head, int w);

int inDegreeCrossGraph(CrossGraph *g, int no);

int outDegreeCrossGraph(CrossGraph *g, int no);

#endif
