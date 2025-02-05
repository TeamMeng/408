#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../13_matrixGraph/matrixGraph.h"

#define INN 1E3

void DijkstraMGraph(const MGraph *graph, int start, int *dist, int *path);

void showShortPath(const int *path, int num, int pos);

#endif
