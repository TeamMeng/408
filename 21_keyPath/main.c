#include "keyPath.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *names[] = {"V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8"};
  int n = sizeof(names) / sizeof(names[0]);
  AGraph *g = createAGraph(n);

  if (g == NULL) {
    return -1;
  }

  initAGraph(g, n, names, 1);

  addAGraphEdge(g, 0, 1, 6);
  addAGraphEdge(g, 0, 2, 4);
  addAGraphEdge(g, 0, 3, 5);
  addAGraphEdge(g, 1, 4, 1);
  addAGraphEdge(g, 2, 4, 1);
  addAGraphEdge(g, 3, 5, 2);
  addAGraphEdge(g, 4, 6, 9);
  addAGraphEdge(g, 4, 7, 7);
  addAGraphEdge(g, 5, 7, 4);
  addAGraphEdge(g, 6, 8, 2);
  addAGraphEdge(g, 7, 8, 4);

  keyPath(g);

  releaseAGraph(g);

  return 0;
}
