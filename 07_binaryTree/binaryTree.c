#include "binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create tree
BinaryTree *createdBinaryTree(TreeNode *root) {
  BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));

  if (tree == NULL) {
    printf("tree malloc failed!\n");
    return NULL;
  }

  if (root) {
    tree->root = root;
    tree->count = 1;
  } else {
    tree->root = NULL;
    tree->count = 0;
  }

  return tree;
}

// release
void releaseBinaryTree(BinaryTree *tree);

// create node
TreeNode *createTreeNode(Element elem) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

  if (node == NULL) {
    printf("node malloc failed!\n");
    return NULL;
  }

  node->elem = elem;
  node->left = node->right = NULL;

  return node;
}

void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left,
                      TreeNode *right) {
  if (tree && parent) {
    parent->left = left;
    parent->right = right;

    if (left) {
      ++tree->count;
    }

    if (right) {
      ++tree->count;
    }
  }
}

void visitTreeNode(TreeNode *node) {
  if (node) {
    printf("\t%c ", node->elem);
  }
}

static void preOrder(TreeNode *node) {
  if (node) {
    visitTreeNode(node);
    preOrder(node->left);
    preOrder(node->right);
  }
}

// pre
void preOrderBTreeRecur(BinaryTree *tree) {
  if (tree) {
    preOrder(tree->root);
  }
}

static void inOrder(TreeNode *node) {
  if (node) {
    inOrder(node->left);
    visitTreeNode(node);
    inOrder(node->right);
  }
}

// in
void inOrderBTreeRecur(BinaryTree *tree) {
  if (tree) {
    inOrder(tree->root);
  }
}

static void postOrder(TreeNode *node) {
  if (node) {
    postOrder(node->left);
    postOrder(node->right);
    visitTreeNode(node);
  }
}

// post
void postOrderBTreeRecur(BinaryTree *tree) {
  if (tree) {
    postOrder(tree->root);
  }
}
