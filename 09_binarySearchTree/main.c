#include "BSearchTree.h"
#include <stdio.h>

const int arr[] = {8, 3, 10, 6, 14, 4, 7, 13};

BSearchTree *init() {
  BSearchTree *tree = createBSearchTree();
  for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
    insertBSTree(tree, arr[i]);
  }
  return tree;
}

int main(int argc, char *argv[]) {
  BSearchTree *tree = init();

  BSNode *node = searchBinarySearchNode(tree, 10);

  if (node) {
    printf("%d\n", node->elem);
  }

  inOrderBinarySearchTree(tree);
  printf("\n");

  releaseBinarySearchTree(tree);
  return 0;
}
