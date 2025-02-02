#include "adjacentGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AGraph *createAGraph(int n) {
  AGraph *g = (AGraph *)malloc(sizeof(AGraph));

  if (g == NULL) {
    printf("AGraph malloc failed!\n");
    return NULL;
  }

  g->nodes = (ArcNode *)malloc(sizeof(ArcNode) * n);

  if (g->nodes == NULL) {
    printf("nodes malloc failed!\n");
    free(g);
    return NULL;
  }

  memset(g->nodes, 0, sizeof(ArcNode) * n);

  return g;
}

void releaseAGraph(AGraph *g) {
  if (g) {
    int count = 0;
    for (int i = 0; i < g->nodeNum; ++i) {
      ArcEdge *node = g->nodes[i].firstEdge;
      while (node) {
        ArcEdge *tmp = node;
        node = tmp->next;
        free(tmp);
        ++count;
      }
    }
    printf("free edges: %d\n", count);
  }
}

void initAGraph(AGraph *g, int num, char *names[], int directed) {
  if (g) {
    g->directed = directed;
    g->edgeNum = 0;
    g->nodeNum = num;
    for (int i = 0; i < num; ++i) {
      g->nodes[i].no = i;
      g->nodes[i].show = names[i];
      g->nodes[i].firstEdge = NULL;
    }
  }
}

static ArcEdge *createArcEdge(int no, int w) {
  ArcEdge *edge = (ArcEdge *)malloc(sizeof(ArcEdge));

  if (edge == NULL) {
    printf("edge malloc failed!\n");
    return NULL;
  }

  edge->weight = w;
  edge->no = no;
  edge->next = NULL;

  return edge;
}

void addAGraphEdge(AGraph *g, int x, int y, int w) {
  if (x < 0 || x >= g->nodeNum || y < 0 || y >= g->nodeNum) {
    return;
  }

  if (g) {
    if (x == y) {
      return;
    }

    ArcEdge *edge = createArcEdge(y, w);
    if (edge == NULL) {
      return;
    }

    edge->next = g->nodes[x].firstEdge;
    g->nodes[x].firstEdge = edge;
    ++g->edgeNum;
    if (g->directed == 0) {
      edge = createArcEdge(x, w);
      if (edge == NULL) {
        return;
      }

      edge->next = g->nodes[y].firstEdge;
      g->nodes[y].firstEdge = edge;
      ++g->edgeNum;
    }
  }
}
