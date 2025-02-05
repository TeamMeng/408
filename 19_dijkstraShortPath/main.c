#include <stdio.h>
#include <stdlib.h>

#include "dijkstraShortPath.h"

void setupMGraph(MGraph *graph) {
  char *names[] = {"0", "1", "2", "3", "4", "5", "6"};
  initMGraph(graph, sizeof(names) / sizeof(names[0]), names, 1, INF);
  addMGraphEdge(graph, 0, 1, 4);
  addMGraphEdge(graph, 0, 2, 6);
  addMGraphEdge(graph, 0, 3, 6);
  addMGraphEdge(graph, 1, 4, 7);
  addMGraphEdge(graph, 1, 2, 1);
  addMGraphEdge(graph, 2, 4, 6);
  addMGraphEdge(graph, 2, 5, 4);
  addMGraphEdge(graph, 3, 2, 2);
  addMGraphEdge(graph, 3, 5, 5);
  addMGraphEdge(graph, 4, 6, 6);
  addMGraphEdge(graph, 5, 4, 1);
  addMGraphEdge(graph, 5, 6, 8);
}

int main() {
  MGraph graph;
  int *dist; // 存储 源点x到其他节点的最短路径权值
  int *path; // 存储 源点到其他节点最短路径中，他的前一个节点信息

  setupMGraph(&graph);
  dist = (int *)malloc(sizeof(int) * graph.nodeNum);
  path = (int *)malloc(sizeof(int) * graph.nodeNum);
  if (dist == NULL || path == NULL) {
    return -1;
  }
  DijkstraMGraph(&graph, 0, dist, path);
  printf("0节点到6节点: %d\n", dist[6]);
  showShortPath(path, graph.nodeNum, 6);
  free(dist);
  free(path);
  return 0;
}
