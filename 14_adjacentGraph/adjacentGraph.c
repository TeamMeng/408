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

  g->visited = (int *)malloc(sizeof(int) * n);

  if (g->visited == NULL) {
    printf("visited malloc failed!\n");
    free(g->nodes);
    free(g);
    return NULL;
  }

  memset(g->nodes, 0, sizeof(ArcNode) * n);
  memset(g->visited, 0, sizeof(int) * n);

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
    free(g->visited);
    free(g);
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

void visitAGraphNode(ArcNode *node) { printf("%s\t", node->show); }

void DFSAGraphTravel(AGraph *g, int v) {
  ArcEdge *p;
  g->visited[v] = 1;
  visitAGraphNode(&g->nodes[v]);
  p = g->nodes[v].firstEdge;
  while (p) {
    if (g->visited[p->no] == 0) {
      DFSAGraphTravel(g, p->no);
    }
    p = p->next;
  }
}

void resetAGraphVisit(AGraph *g) {
  if (g && g->visited) {
    memset(g->visited, 0, sizeof(int) * g->nodeNum);
  }
}

void BFSAGraphTravel(AGraph *g, int v) {
  int *que = (int *)malloc(sizeof(int) * g->nodeNum);
  if (que == NULL) {
    return;
  }

  int rear = 0, front = 0;
  rear = (rear + 1) % g->nodeNum;
  que[rear] = v;
  int cur = 0;
  ArcEdge *p;

  while (front != rear) {
    front = (front + 1) % g->nodeNum;
    cur = que[front];
    visitAGraphNode(&g->nodes[cur]);
    g->visited[cur] = 1;

    p = g->nodes[cur].firstEdge;
    while (p) {
      if (g->visited[p->no] == 0) {
        rear = (rear + 1) % g->nodeNum;
        que[rear] = p->no;
        g->visited[p->no] = 1;
      }
      p = p->next;
    }
  }

  free(que);
}
