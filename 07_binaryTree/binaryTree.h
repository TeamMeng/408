#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef int Element;

typedef struct TreeNode {
  Element elem;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

typedef TreeNode *pTreeNode;

typedef struct {
  TreeNode *root;
  int count;
} BinaryTree;

// create tree
BinaryTree *createdBinaryTree(TreeNode *root);

// release
void releaseBinaryTree(BinaryTree *tree);

// create node
TreeNode *createTreeNode(Element elem);

// insert
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left,
                      TreeNode *right);

void visitTreeNode(TreeNode *node);

// pre recur
void preOrderBTreeRecur(BinaryTree *tree);

// in recur
void inOrderBTreeRecur(BinaryTree *tree);

// post recur
void postOrderBTreeRecur(BinaryTree *tree);

// level order
void levelOrderBTree(BinaryTree *tree);

// pre no recur
void preOrderBTreeNoRecur(BinaryTree *tree);

// in no recur
void inOrderBTreeNoRecur(BinaryTree *tree);

// post no recur
void postOrderBTreeNoRecur(BinaryTree *tree);
#endif
