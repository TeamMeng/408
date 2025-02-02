#include "adjacentGraph.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *names[] = {"A", "B", "C", "D", "E"};
  AGraph *g = createAGraph(sizeof(names) / sizeof(names[0]));
  initAGraph(g, sizeof(names) / sizeof(names[0]), names, 1);

  addAGraphEdge(g, 0, 1, 1);
  addAGraphEdge(g, 0, 3, 1);
  addAGraphEdge(g, 0, 4, 1);
  addAGraphEdge(g, 1, 2, 1);
  addAGraphEdge(g, 1, 4, 1);
  addAGraphEdge(g, 2, 0, 1);
  addAGraphEdge(g, 3, 2, 1);

  printf("edge: %d\n", g->edgeNum);

  DFSAGraphTravel(g, 0);
  printf("\n");
  resetAGraphVisit(g);

  BFSAGraphTravel(g, 0);
  printf("\n");

  releaseAGraph(g);
  return 0;
}
