#ifndef BSREACHTREE_H
#define BSREACHTREE_H

typedef int Element;

typedef struct Node {
  Element elem;
  struct Node *left;
  struct Node *right;
} BSNode;

typedef struct {
  BSNode *root;
  int count;
} BSearchTree;

// create tree
BSearchTree *createBSearchTree();

// create node
BSNode *createBSNode(Element elem);

// release
void releaseBinarySearchTree(BSearchTree *tree);

// insert no recur
void insertBSTree(BSearchTree *tree, Element elem);

// insert recur
void insertBSTreeRecur(BSearchTree *tree, Element elem);

// search
BSNode *searchBinarySearchNode(BSearchTree *tree, Element elem);

// in
void inOrderBinarySearchTree(BSearchTree *tree);

// delete no recur
void deleteBSTreeNoRecur(BSearchTree *tree, Element elem);

// delete recur
void deleteBSTreeRecur(BSearchTree *tree, Element elem);

// heigh
int heightBSNode(BSNode *node);
#endif
