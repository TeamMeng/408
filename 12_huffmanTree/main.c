#include "huffmanTree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int w[] = {5, 29, 7, 8, 14, 23, 3, 11};
  int n = sizeof(w) / sizeof(w[0]);
  int m = n * 2 - 1;
  HuffmanTree tree = createHuffmanTree(w, n);

  if (tree == NULL) {
    return -1;
  }

  for (int i = 1; i <= m; ++i) {
    printf("%d %d %d %d\n", tree[i].weight, tree[i].parent, tree[i].lChild,
           tree[i].rChild);
  }

  HuffmanCode *codes = createHuffmanCode(tree, n);

  for (int i = 0; i < n; ++i) {
    printf("%s\n", codes[i]);
  }

  releaseHuffmanTree(tree);
  releaseHuffmanCode(codes, n);
  return 0;
}
