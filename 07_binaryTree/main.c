#include "binaryTree.h"
#include <stdio.h>
#include <string.h>

BinaryTree *initTree() {
  TreeNode *nodeA = createTreeNode('A');
  TreeNode *nodeB = createTreeNode('B');
  TreeNode *nodeC = createTreeNode('C');
  TreeNode *nodeD = createTreeNode('D');
  TreeNode *nodeE = createTreeNode('E');
  TreeNode *nodeF = createTreeNode('F');
  TreeNode *nodeG = createTreeNode('G');
  TreeNode *nodeH = createTreeNode('H');
  TreeNode *nodeI = createTreeNode('I');

  BinaryTree *tree = createdBinaryTree(nodeA);
  insertBinaryTree(tree, nodeA, nodeB, nodeE);
  insertBinaryTree(tree, nodeB, NULL, nodeC);
  insertBinaryTree(tree, nodeE, NULL, nodeF);
  insertBinaryTree(tree, nodeC, nodeD, NULL);
  insertBinaryTree(tree, nodeF, nodeG, NULL);
  insertBinaryTree(tree, nodeG, nodeH, nodeI);

  return tree;
}

int main(int argc, char *argv[]) {
  BinaryTree *tree = initTree();
  printf("pre: ");
  preOrderBTreeRecur(tree);
  printf("\nin: ");
  inOrderBTreeRecur(tree);
  printf("\npost: ");
  postOrderBTreeRecur(tree);

  return 0;
}
