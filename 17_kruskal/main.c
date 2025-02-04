#include "kruskal.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  MGraph g;
  char *names[] = {"A", "B", "C", "D", "E", "F", "G"};

  int n = sizeof(names) / sizeof(names[0]);

  initMGraph(&g, n, names, 0, 0);

  addMGraphEdge(&g, 0, 1, 12);
  addMGraphEdge(&g, 0, 5, 16);
  addMGraphEdge(&g, 0, 6, 14);
  addMGraphEdge(&g, 1, 2, 10);
  addMGraphEdge(&g, 1, 5, 7);
  addMGraphEdge(&g, 2, 5, 6);
  addMGraphEdge(&g, 2, 4, 5);
  addMGraphEdge(&g, 2, 3, 3);
  addMGraphEdge(&g, 3, 4, 4);
  addMGraphEdge(&g, 4, 5, 2);
  addMGraphEdge(&g, 4, 6, 8);
  addMGraphEdge(&g, 5, 6, 9);

  EdgeSet *set = (EdgeSet *)malloc(sizeof(EdgeSet) * g.edgeNum);

  if (set == NULL) {
    printf("set malloc failed!\n");
    return 0;
  }

  int num = initEdgeSet(&g, set);

  printf("edgeSet num: %d\n", num);

  sortEdgeSet(set, num);

  EdgeSet *result = (EdgeSet *)malloc(sizeof(EdgeSet) * (g.nodeNum - 1));

  int sumW = KruskalMGraph(&g, set, num, result);

  printf("kruskal sum of weight: %d\n", sumW);

  for (int i = 0; i < g.nodeNum - 1; ++i) {
    printf("edge: %d: [%s] --- <%d> --- [%s]\n", i + 1,
           g.vex[result[i].begin].show, result[i].weight,
           g.vex[result[i].end].show);
  }

  free(set);
  free(result);

  return 0;
}
