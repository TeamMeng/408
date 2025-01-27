#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef int Element;

typedef struct AVLNode {
  Element elem;
  struct AVLNode *left;
  struct AVLNode *right;
  int height;
} AVLNode;

typedef struct {
  AVLNode *root;
  int count;
} AVLTree;

// create tree
AVLTree *createAVLTree();

// release tree
void releaseAVLTree(AVLTree *tree);

// visit
void visitAVLNode(AVLNode *node);

// in order
void inOrderAVLTree(AVLTree *tree);

// insert
void insertAVLTree(AVLTree *tree, Element elem);

// create node
AVLNode *createAVLNode(Element elem);

// delete node
void deleteAVLTree(AVLTree *tree, Element elem);
#endif
