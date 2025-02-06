#include "topologicalSort.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *names[] = {"0", "1", "2", "3", "4", "5", "6"};
  int n = sizeof(names) / sizeof(names[0]);
  AGraph *g = createAGraph(n);

  if (g == NULL) {
    return -1;
  }

  initAGraph(g, n, names, 1);

  addAGraphEdge(g, 0, 1, 1);
  addAGraphEdge(g, 0, 2, 1);
  addAGraphEdge(g, 0, 3, 1);
  addAGraphEdge(g, 1, 2, 1);
  addAGraphEdge(g, 1, 4, 1);
  addAGraphEdge(g, 2, 4, 1);
  addAGraphEdge(g, 2, 5, 1);
  addAGraphEdge(g, 3, 5, 1);
  addAGraphEdge(g, 4, 6, 1);
  addAGraphEdge(g, 5, 4, 1);
  addAGraphEdge(g, 5, 6, 1);

  if (TopologicalSort(g)) {
    printf("无环\n");
  } else {
    printf("有环\n");
  }

  releaseAGraph(g);

  return 0;
}
