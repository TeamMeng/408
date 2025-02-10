#include "matrixGraph.h"
#include <stdio.h>

#define MAX_SIZE 20

static int dist[MAX_SIZE][MAX_SIZE];
static int path[MAX_SIZE][MAX_SIZE];

void shortPathFloyd(MGraph *g) {
  for (int i = 0; i < g->nodeNum; ++i) {
    for (int j = 0; j < g->nodeNum; ++j) {
      dist[i][j] = g->edges[i][j];
      if (dist[i][j] < INF && i != j) {
        path[i][j] = i;
      } else {
        path[i][j] = -1;
      }
    }
  }

  // 从[0..n)激活
  for (int k = 0; k < g->nodeNum; ++k) {
    // k状态下第i行
    for (int i = 0; i < g->nodeNum; ++i) {
      // k状态下第i行j列
      for (int j = 0; j < g->nodeNum; ++j) {
        if (dist[i][k] < INF && dist[k][j] < INF &&
            dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = path[k][j];
        }
      }
    }
  }
}

void printfPath(int i, int j) {
  if (i == j) {
    printf("%d ", i);
    return;
  }
  int k = path[i][j];
  printfPath(i, k);
  printf("%d ", j);
}

int main(int argc, char *argv[]) {
  MGraph g;
  char *names[] = {"V0", "V1", "V2", "V3"};
  initMGraph(&g, sizeof(names) / sizeof(names[0]), names, 1, INF);

  for (int i = 0; i < g.nodeNum; ++i) {
    g.edges[i][i] = 0;
  }

  addMGraphEdge(&g, 0, 1, 1);
  addMGraphEdge(&g, 0, 3, 4);
  addMGraphEdge(&g, 1, 2, 9);
  addMGraphEdge(&g, 1, 3, 2);
  addMGraphEdge(&g, 2, 0, 3);
  addMGraphEdge(&g, 2, 1, 5);
  addMGraphEdge(&g, 2, 3, 8);
  addMGraphEdge(&g, 3, 2, 6);

  shortPathFloyd(&g);

  for (int i = 0; i < g.nodeNum; ++i) {
    for (int j = 0; j < g.nodeNum; ++j) {
      printf("%d\t", dist[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printfPath(1, 0);

  return 0;
}
