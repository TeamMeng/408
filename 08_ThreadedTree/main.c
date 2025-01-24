#include "threadedBTree.h"
#include <string.h>

ThreadedBTree *initTree() {
  TBTNode *nodeA = createTBTNode('A');
  TBTNode *nodeB = createTBTNode('B');
  TBTNode *nodeC = createTBTNode('C');
  TBTNode *nodeD = createTBTNode('D');
  TBTNode *nodeE = createTBTNode('E');
  TBTNode *nodeF = createTBTNode('F');
  TBTNode *nodeG = createTBTNode('G');
  TBTNode *nodeH = createTBTNode('H');
  TBTNode *nodeK = createTBTNode('K');

  ThreadedBTree *tree = createThreadedBTree(nodeA);

  insertThreadedBTree(tree, nodeA, nodeB, nodeE);
  insertThreadedBTree(tree, nodeB, NULL, nodeC);
  insertThreadedBTree(tree, nodeE, NULL, nodeF);
  insertThreadedBTree(tree, nodeC, nodeD, NULL);
  insertThreadedBTree(tree, nodeF, nodeG, NULL);
  insertThreadedBTree(tree, nodeG, nodeH, nodeK);
  return tree;
}

int main(int argc, char *argv[]) {
  ThreadedBTree *tree = initTree();

  inOrderThreadedBTree(tree);
  inOrderTBTree(tree);

  releaseThreadedBTree(tree);
  return 0;
}
