#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../13_matrixGraph/matrixGraph.h"

/* 从边的角度求图的最小生成树，更适合求边稀疏的图
 * 将所有的边按照权值的大小进行升序，然后从小到大一一判断
 * 1. 如果这个边不会与之前选择的所有边组成回路，就可以作为最小生成树
 * 2. 放置，舍去
 * 循环，直到具有n个顶点的连通图筛选出n - 1条边
 * 引入一个数据结构，边集数组，保存边和节点的关系
 * 简化版： 从边集数组里，找最小的边，判断2个顶点会不会构成一个环
 * */

typedef struct {
  int begin;
  int end;
  int weight;
} EdgeSet;

int initEdgeSet(const MGraph *g, EdgeSet *set);

void sortEdgeSet(EdgeSet *set, int num);

int KruskalMGraph(const MGraph *g, const EdgeSet *set, int num,
                  EdgeSet *result);

#endif
