#include "BSearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create
BSearchTree *createBSearchTree() {
  BSearchTree *tree = (BSearchTree *)malloc(sizeof(BSearchTree));

  if (tree == NULL) {
    printf("tree malloc failed!\n");
    return NULL;
  }

  tree->root = NULL;
  tree->count = 0;

  return tree;
}

static void destroyTreeNode(BSearchTree *tree, BSNode *node) {
  if (node) {
    destroyTreeNode(tree, node->left);
    destroyTreeNode(tree, node->right);
    --tree->count;
  }
}

// release
void releaseBinarySearchTree(BSearchTree *tree) {
  if (tree) {
    destroyTreeNode(tree, tree->root);
    printf("tree is free, free's count is %d\n", tree->count);
    free(tree);
  }
}

// insert no recur
void insertBSTree(BSearchTree *tree, Element elem) {
  if (tree == NULL) {
    return;
  }

  BSNode *node = createBSNode(elem);

  if (node == NULL) {
    return;
  }

  BSNode *cur = tree->root;
  BSNode *pre = NULL;
  while (cur) {
    pre = cur;
    if (elem > cur->elem) {
      cur = cur->right;
    } else if (elem < cur->elem) {
      cur = cur->left;
    } else {
      return;
    }
  }

  if (pre && elem > pre->elem) {
    pre->right = node;
  } else if (pre && elem < pre->elem) {
    pre->left = node;
  } else {
    tree->root = node;
  }

  ++tree->count;
}

// search

BSNode *searchBinarySearchNode(BSearchTree *tree, Element elem) {
  BSNode *node = tree->root;
  while (node) {
    if (elem > node->elem) {
      node = node->right;
    } else if (elem < node->elem) {
      node = node->left;
    } else {
      return node;
    }
  }
  return NULL;
}

// create node
BSNode *createBSNode(Element elem) {
  BSNode *node = (BSNode *)malloc(sizeof(BSNode));

  if (node == NULL) {
    printf("node malloc failed!\n");
    return NULL;
  }

  node->left = node->right = NULL;
  node->elem = elem;

  return node;
}

static void inOrderBinarySearchNode(BSNode *node) {
  if (node) {
    inOrderBinarySearchNode(node->left);
    printf("%d\t", node->elem);
    inOrderBinarySearchNode(node->right);
  }
}

// in
void inOrderBinarySearchTree(BSearchTree *tree) {
  if (tree) {
    inOrderBinarySearchNode(tree->root);
  }
}
