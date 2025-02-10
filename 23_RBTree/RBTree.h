#ifndef RB_TREE_H
#define RB_TREE_H

enum RBColor { RED, BLACK };

typedef int keyType;

// 红黑树节点结构
typedef struct RBNode {
  char color;
  keyType key;
  struct RBNode *left;
  struct RBNode *right;
  struct RBNode *parent;
} RBNode;

typedef struct {
  RBNode *root;
  int count;
} RBTree;

RBTree *createRBTree();

void releaseRBTree(RBTree *tree);

void insertRBTree(RBTree *tree, keyType e);

void printRBTree(RBNode *node, int key, int dir);

#endif
