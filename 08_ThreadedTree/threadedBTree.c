#include "threadedBTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create tree
ThreadedBTree *createThreadedBTree(TBTNode *root) {
  ThreadedBTree *tree = (ThreadedBTree *)malloc(sizeof(ThreadedBTree));

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

static void freeTBTNode(ThreadedBTree *tree, TBTNode *node) {
  if (node) {
    if (node->lTag == 0) {
      freeTBTNode(tree, node->left);
    }
    if (node->rTag == 0) {
      freeTBTNode(tree, node->right);
    }
    free(node);
    --tree->count;
  }
}

// release
void releaseThreadedBTree(ThreadedBTree *tree) {
  if (tree) {
    freeTBTNode(tree, tree->root);
    printf("tree is free, tree's count is %d\n", tree->count);
    free(tree);
  }
}

// create node
TBTNode *createTBTNode(Element elem) {
  TBTNode *node = (TBTNode *)malloc(sizeof(TBTNode));
  if (node == NULL) {
    printf("node malloc failed!\n");
    return NULL;
  }

  node->left = node->right = NULL;
  node->lTag = node->rTag = 0;
  node->elem = elem;

  return node;
}

// insert
void insertThreadedBTree(ThreadedBTree *tree, TBTNode *parent, TBTNode *left,
                         TBTNode *right) {
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

void visitTBTNode(TBTNode *node) {
  if (node) {
    printf("\t%c", node->elem);
  }
}

static TBTNode *pre = NULL;

static void inOrderThreadeding(TBTNode *node) {
  if (node) {
    inOrderThreadeding(node->left);
    if (node->left == NULL) {
      node->left = pre;
      node->lTag = 1;
    }
    if (pre && pre->right == NULL) {
      pre->right = node;
      pre->rTag = 1;
    }
    pre = node;
    inOrderThreadeding(node->right);
  }
}

// 中序线索化树，在中序遍历的过程中，建立左右孩子为空指针的值
void inOrderThreadedBTree(ThreadedBTree *tree) {
  if (tree) {
    inOrderThreadeding(tree->root);
  }
}

// 按照虞姬线索化后的树，进行中序遍历
void inOrderTBTree(ThreadedBTree *tree) {
  if (!tree) {
    return;
  }
  TBTNode *node = tree->root;
  while (node) {
    while (node->lTag == 0) {
      node = node->left;
    }
    visitTBTNode(node);
    while (node->rTag && node->right) {
      node = node->right;
      visitTBTNode(node);
    }
    node = node->right;
  }
}
