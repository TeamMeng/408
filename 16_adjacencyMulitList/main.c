#include "adjacencyMultitList.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *names[] = {"V0", "V1", "V2", "V3", "V4"};
  AdjacencyMultiList *g = createMultiList(sizeof(names) / sizeof(names[0]));
  insertMultiListEdge(g, 0, 3, 1);
  insertMultiListEdge(g, 0, 1, 1);
  insertMultiListEdge(g, 1, 4, 1);
  insertMultiListEdge(g, 2, 1, 1);
  insertMultiListEdge(g, 2, 3, 1);
  insertMultiListEdge(g, 2, 4, 1);

  printf("%d\n", g->edgeNum);
  deleteMultiListEdge(g, 2, 3);
  printf("%d\n", g->edgeNum);

  return 0;
}
