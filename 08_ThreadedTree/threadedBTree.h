#ifndef THREADEDBTREE_H
#define THREADEDBTREE_H

typedef int Element;

typedef struct TreeNode {
  Element elem;
  struct TreeNode *left;
  struct TreeNode *right;
  int lTag; // 0表示left指向左节点，1表示left指向前驱
  int rTag; // 0表示right指向右节点，1表示right指向后驱
} TBTNode;

typedef struct {
  TBTNode *root;
  int count;
} ThreadedBTree;

// create tree
ThreadedBTree *createThreadedBTree(TBTNode *root);

// release
void releaseThreadedBTree(ThreadedBTree *tree);

// create node
TBTNode *createTBTNode(Element elem);

// insert
void insertThreadedBTree(ThreadedBTree *tree, TBTNode *parent, TBTNode *left,
                         TBTNode *right);

void visitTBTNode(TBTNode *node);

// 中序线索化树，在中序遍历的过程中，建立左右孩子为空指针的值
void inOrderThreadedBTree(ThreadedBTree *tree);

// 按照虞姬线索化后的树，进行中序遍历
void inOrderTBTree(ThreadedBTree *tree);
#endif
