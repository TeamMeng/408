#include "huffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void selectNode(HuffmanTree tree, int n, int *s1, int *s2) {
  int mi = 0;
  for (int i = 1; i <= n; ++i) {
    if (tree[i].parent == 0) {
      mi = i;
      break;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (tree[i].parent == 0 && tree[i].weight < tree[mi].weight) {
      mi = i;
    }
  }

  *s1 = mi;

  for (int i = 1; i <= n; ++i) {
    if (tree[i].parent == 0 && i != *s1) {
      mi = i;
      break;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (tree[i].parent == 0 && tree[i].weight < tree[mi].weight && i != *s1) {
      mi = i;
    }
  }

  *s2 = mi;
}

HuffmanTree createHuffmanTree(const int *w, int n) {
  HuffmanTree tree;

  int m = n * 2 - 1;

  tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (m + 1));

  if (tree == NULL) {
    printf("tree malloc failed!\n");
    return NULL;
  }

  for (int i = 1; i <= m; ++i) {
    if (i <= n) {
      tree[i].weight = w[i - 1];
    } else {
      tree[i].weight = 0;
    }
    tree[i].parent = tree[i].lChild = tree[i].rChild = 0;
  }

  for (int i = n + 1; i <= m; ++i) {
    int s1 = 0, s2 = 0;
    selectNode(tree, i - 1, &s1, &s2);
    tree[i].lChild = s1;
    tree[i].rChild = s2;
    tree[i].weight = tree[s1].weight + tree[s2].weight;
    tree[s1].parent = tree[s2].parent = i;
  }

  return tree;
}

void releaseHuffmanTree(HuffmanTree tree) {
  if (tree) {
    free(tree);
  }
}

HuffmanCode *createHuffmanCode(HuffmanTree tree, int n) {
  char *tmp = (char *)malloc(sizeof(char) * n);
  HuffmanCode *codes = (HuffmanCode *)malloc(sizeof(HuffmanCode) * n);

  if (codes == NULL) {
    printf("codes malloc failed!\n");
    return NULL;
  }

  memset(codes, 0, sizeof(HuffmanCode) * n);

  int start;
  int p;
  int pos;

  for (int i = 1; i <= n; ++i) {
    pos = i;
    start = n - 1;
    tmp[start] = '\0';
    p = tree[i].parent;
    while (p) {
      --start;
      tmp[start] = tree[p].lChild == pos ? '0' : '1';
      pos = p;
      p = tree[p].parent;
    }
    codes[i - 1] = (HuffmanCode)malloc(sizeof(char) * (n - start));
    strcpy(codes[i - 1], &tmp[start]);
  }

  free(tmp);

  return codes;
}

void releaseHuffmanCode(HuffmanCode *codes, int n) {
  if (codes) {
    for (int i = 0; i < n; ++i) {
      if (codes[i]) {
        free(codes[i]);
      }
    }
    free(codes);
  }
}
