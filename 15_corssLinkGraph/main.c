#include "crossLinkGraph.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *names[] = {"V0", "V1", "V2", "V3", "V4"};
  CrossGraph *g = createCrossGraph(sizeof(names) / sizeof(names[0]));

  if (g == NULL) {
    return -1;
  }

  initCrossGraph(g, sizeof(names) / sizeof(names[0]), names);

  addCrossArc(g, 0, 3, 1);
  addCrossArc(g, 1, 0, 1);
  addCrossArc(g, 1, 2, 1);
  addCrossArc(g, 2, 1, 1);
  addCrossArc(g, 2, 0, 1);

  printf("V0的入度为: %d\n", inDegreeCrossGraph(g, 0));
  printf("V0的出度为: %d\n", outDegreeCrossGraph(g, 0));

  releaseCorssGraph(g);

  return 0;
}
