#include "topologicalSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TopologicalSort(AGraph *g) {
  int *inDegree = (int *)malloc(sizeof(int) * g->nodeNum);

  if (inDegree == NULL) {
    printf("inDergee malloc failed!\n");
    return -1;
  }

  memset(inDegree, 0, sizeof(int) * g->nodeNum);

  for (int i = 0; i < g->nodeNum; ++i) {
    ArcEdge *edge = g->nodes[i].firstEdge;
    while (edge) {
      ++inDegree[edge->no];
      edge = edge->next;
    }
  }

  int *stack = (int *)malloc(sizeof(int) * g->nodeNum);
  if (stack == NULL) {
    printf("stack malloc failed!\n");
    free(inDegree);
    return -1;
  }
  int top = -1;

  for (int i = 0; i < g->nodeNum; ++i) {
    if (inDegree[i] == 0) {
      stack[++top] = i;
    }
  }

  int count = 0;
  while (top != -1) {
    int idx = stack[top--];
    ++count;
    visitAGraphNode(&g->nodes[idx]);
    ArcEdge *edge = g->nodes[idx].firstEdge;
    while (edge) {
      --inDegree[edge->no];
      if (inDegree[edge->no] == 0) {
        stack[++top] = edge->no;
      }
      edge = edge->next;
    }
  }

  free(inDegree);
  free(stack);

  return count == g->nodeNum;
}
