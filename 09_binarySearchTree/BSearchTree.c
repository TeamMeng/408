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

static void deleteMiniNode(BSNode *node) {
  BSNode *pre = node;
  BSNode *mini = node->right;

  while (mini && mini->left) {
    pre = mini;
    mini = mini->left;
  }

  node->elem = mini->elem;
  if (pre->elem == node->elem) {
    pre->right = mini->right;
  } else {
    pre->left = mini->right;
  }

  if (mini) {
    free(mini);
  }

  return;
}

/*
 * 1. 找到这个节点
 * 2. 判断度的情况
 */
void deleteBSTreeNoRecur(BSearchTree *tree, Element elem) {
  if (!tree) {
    return;
  }

  BSNode *cur = tree->root;
  BSNode *pre = NULL;
  BSNode *tmp = NULL;

  while (cur) {
    if (elem > cur->elem) {
      pre = cur;
      cur = cur->right;
    } else if (elem < cur->elem) {
      pre = cur;
      cur = cur->left;
    } else {
      break;
    }
  }

  if (pre && cur) {
    if (cur->left == NULL) {
      tmp = cur->right;
    } else if (cur->right == NULL) {
      tmp = cur->left;
    } else {
      // 度为2找后继
      deleteMiniNode(cur);
      --tree->count;
      return;
    }

    if (cur->elem < elem) {
      pre->left = tmp;
    } else {
      pre->right = tmp;
    }

    free(cur);
    --tree->count;
    return;
  }

  if (pre == NULL) {
    deleteMiniNode(cur);
    --tree->count;
  }
}

static BSNode *insertBSNodeRecur(BSearchTree *tree, BSNode *node,
                                 Element elem) {
  if (node == NULL) {
    ++tree->count;
    return createBSNode(elem);
  }

  if (elem > node->elem) {
    node->right = insertBSNodeRecur(tree, node->right, elem);
  } else if (elem < node->elem) {
    node->left = insertBSNodeRecur(tree, node->left, elem);
  }

  return node;
}

// insert recur
void insertBSTreeRecur(BSearchTree *tree, Element elem) {
  if (tree) {
    tree->root = insertBSNodeRecur(tree, tree->root, elem);
  }
}

// heigh
int heightBSNode(BSNode *node) {
  if (node == NULL) {
    return 0;
  }

  int left = heightBSNode(node->left);
  int right = heightBSNode(node->right);

  return left >= right ? left + 1 : right + 1;
}

static BSNode *miniValueBSNode(BSNode *node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

static BSNode *deleteBSNodeRecur(BSearchTree *tree, BSNode *node,
                                 Element elem) {

  if (node == NULL) {
    return NULL;
  }

  if (elem > node->elem) {
    node->right = deleteBSNodeRecur(tree, node->right, elem);
  } else if (elem < node->elem) {
    node->left = deleteBSNodeRecur(tree, node->left, elem);
  } else {
    BSNode *tmp;
    if (node->left == NULL) {
      tmp = node->right;
      free(node);
      --tree->count;
      return tmp;
    }
    if (node->right == NULL) {
      tmp = node->left;
      free(node);
      --tree->count;
      return tmp;
    }
    tmp = miniValueBSNode(node->right);
    node->elem = tmp->elem;
    node->right = deleteBSNodeRecur(tree, node->right, tmp->elem);
  }

  return node;
}

// delete recur
void deleteBSTreeRecur(BSearchTree *tree, Element elem) {
  if (tree) {
    deleteBSNodeRecur(tree, tree->root, elem);
  }
}
