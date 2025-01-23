#include "binaryTree.h"
#include "arrayQueue.h"
#include "arrayStack.h"
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

static void destroyTreeNode(BinaryTree *tree, TreeNode *node) {
  if (node) {
    destroyTreeNode(tree, node->left);
    destroyTreeNode(tree, node->right);
    --tree->count;
  }
}

// release
void releaseBinaryTree(BinaryTree *tree) {
  if (tree && tree->root) {
    destroyTreeNode(tree, tree->root);
    printf("tree is free, tree's count is %d\n", tree->count);
    free(tree);
  }
}

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

// level order
void levelOrderBTree(BinaryTree *tree) {
  if (!tree && !tree->root) {
    return;
  }

  ArrayQueue *q = createdArrayQueue();
  pushArrayQueue(q, tree->root);
  pTreeNode node;
  while (popArrayQueue(q, &node) != -1) {
    visitTreeNode(node);
    if (node->left) {
      pushArrayQueue(q, node->left);
    }
    if (node->right) {
      pushArrayQueue(q, node->right);
    }
  }
  releaseArrayQueue(q);
}

/* 非递归的先序遍历
 * 1.压入根节点到栈
 * 2.弹出元素，访问改元素
 * 3.有右压右，有左压左
 */
void preOrderBTreeNoRecur(BinaryTree *tree) {
  if (!tree && !tree->root) {
    return;
  }

  ArrayStack *stack = createdArrayStack();

  pushArrayStack(stack, tree->root);

  pTreeNode elem;
  while (popArrayStack(stack, &elem) != -1 && elem) {
    visitTreeNode(elem);
    if (elem->right) {
      pushArrayStack(stack, elem->right);
    }
    if (elem->left) {
      pushArrayStack(stack, elem->left);
    }
  }

  releaseArrayStack(stack);
}

// in no recur
void inOrderBTreeNoRecur(BinaryTree *tree) {
  if (!tree && !tree->root) {
    return;
  }
  ArrayStack *stack = createdArrayStack();
  pTreeNode node = tree->root;

  while (stack->top >= 0 || node) {
    if (node) {
      pushArrayStack(stack, node);
      node = node->left;
    } else {
      popArrayStack(stack, &node);
      visitTreeNode(node);
      node = node->right;
    }
  }

  releaseArrayStack(stack);
}

// post no recur
void postOrderBTreeNoRecur(BinaryTree *tree) {
  if (!tree && !tree->root) {
    return;
  }

  ArrayStack *l = createdArrayStack();
  ArrayStack *r = createdArrayStack();

  pushArrayStack(l, tree->root);
  pTreeNode elem;
  while (popArrayStack(l, &elem) != -1 && elem) {
    pushArrayStack(r, elem);
    if (elem->left) {
      pushArrayStack(l, elem->left);
    }
    if (elem->right) {
      pushArrayStack(l, elem->right);
    }
  }

  while (popArrayStack(r, &elem) != -1 && elem) {
    visitTreeNode(elem);
  }

  releaseArrayStack(l);
  releaseArrayStack(r);
}
