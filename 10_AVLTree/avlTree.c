
#include "avlTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create tree
AVLTree *createAVLTree() {
  AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));

  if (tree == NULL) {
    printf("tree malloc failed!\n");
    return NULL;
  }

  tree->root = NULL;
  tree->count = 0;

  return tree;
}

static void deleteAVLNode(AVLNode *node) {
  if (node) {
    deleteAVLNode(node->left);
    deleteAVLNode(node->right);
    free(node);
  }
}

// release tree
void releaseAVLTree(AVLTree *tree) {
  if (tree) {
    deleteAVLNode(tree->root);
  }
}

// visit
void visitAVLNode(AVLNode *node) { printf("%c\t", node->elem); }

static void inOrderAVLNode(AVLNode *node) {
  if (node) {
    inOrderAVLNode(node->left);
    visitAVLNode(node);
    inOrderAVLNode(node->right);
  }
}

// in order
void inOrderAVLTree(AVLTree *tree) {
  if (tree) {
    inOrderAVLNode(tree->root);
  }
}
