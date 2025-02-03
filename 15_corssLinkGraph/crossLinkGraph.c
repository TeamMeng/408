#include "crossLinkGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CrossGraph *createCrossGraph(int n) {
  CrossGraph *g = (CrossGraph *)malloc(sizeof(CrossGraph));

  if (g == NULL) {
    printf("graph malloc failed!\n");
    return NULL;
  }

  CrossVertex *nodes = (CrossVertex *)malloc(sizeof(CrossVertex) * n);

  if (nodes == NULL) {
    free(g);
    printf("nodes malloc failed!\n");
    return NULL;
  }

  g->nodes = nodes;
  g->edgeNum = 0;

  return g;
}

void initCrossGraph(CrossGraph *g, int num, char *names[]) {
  if (g) {
    g->nodeNum = num;
    for (int i = 0; i < num; ++i) {
      g->nodes[i].no = i;
      g->nodes[i].show = names[i];
      g->nodes[i].firstIn = g->nodes[i].firstOut = NULL;
    }
  }
}

void releaseCorssGraph(CrossGraph *g) {
  if (g && g->nodes) {
    int count = 0;
    for (int i = 0; i < g->nodeNum; ++i) {
      ArcBox *box = g->nodes[i].firstOut;
      while (box) {
        ArcBox *tmp = box;
        box = tmp->tailNext;
        free(tmp);
        ++count;
      }
    }
    printf("release %d edges\n", count);
    free(g->nodes);
    free(g);
  }
}

void addCrossArc(CrossGraph *g, int tail, int head, int w) {
  ArcBox *box = (ArcBox *)malloc(sizeof(ArcBox));
  if (box == NULL) {
    return;
  }

  box->weight = w;
  box->tailVertex = tail;
  box->tailNext = g->nodes[tail].firstOut;
  g->nodes[tail].firstOut = box;

  box->headVertex = head;
  box->headNext = g->nodes[head].firstIn;
  g->nodes[head].firstIn = box;

  ++g->edgeNum;
}

int inDegreeCrossGraph(CrossGraph *g, int no) {
  int count = 0;
  if (g) {
    ArcBox *box = g->nodes[no].firstIn;
    while (box) {
      box = box->headNext;
      ++count;
    }
  }
  return count;
}

int outDegreeCrossGraph(CrossGraph *g, int no) {
  int count = 0;
  if (g) {
    ArcBox *box = g->nodes[no].firstOut;
    while (box) {
      box = box->tailNext;
      ++count;
    }
  }
  return count;
}
