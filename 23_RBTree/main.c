#include "RBTree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int data[] = {55, 40, 65, 60, 75, 57, 63, 56};
  RBTree *tree = createRBTree();

  if (tree == NULL) {
    return -1;
  }

  for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
    insertRBTree(tree, data[i]);
  }

  printRBTree(tree->root, tree->root->key, 0);

  releaseRBTree(tree);

  return 0;
}
