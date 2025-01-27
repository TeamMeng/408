#include <stdio.h>

#include "avlTree.h"

int main(int argc, char const *argv[]) {
  AVLTree *tree = createAVLTree();

  Element data[] = {10, 20, 30, 40, 50, 60, 70, 80};

  for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
    insertAVLTree(tree, data[i]);
  }

  inOrderAVLTree(tree);
  printf("\nheight: %d\n", tree->root->height);

  deleteAVLTree(tree, 60);

  inOrderAVLTree(tree);

  releaseAVLTree(tree);

  return 0;
}
