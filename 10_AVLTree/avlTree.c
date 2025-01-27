#include "avlTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int maxNum(int a, int b) { return a > b ? a : b; }

static int h(AVLNode *node) {
  if (node == NULL) {
    return 0;
  } else {
    return node->height;
  }
}

static int getBalance(AVLNode *node) {
  if (node == NULL) {
    return 0;
  }

  return h(node->left) - h(node->right);
}

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

static void postDeleteAVLNode(AVLNode *node) {
  if (node) {
    postDeleteAVLNode(node->left);
    postDeleteAVLNode(node->right);
    free(node);
  }
}

// release tree
void releaseAVLTree(AVLTree *tree) {
  if (tree) {
    postDeleteAVLNode(tree->root);
    free(tree);
  }
}

// visit
void visitAVLNode(AVLNode *node) {
  if (node) {
    printf("\t<%d:%d>", node->elem, node->height);
  }
}

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

/* 左旋操作
 *   px
 *   |
 *    x
 *  /   \
 *  lx    y
 *      /   \
 *      ly   ry
 */
static AVLNode *leftRotate(AVLNode *x) {
  AVLNode *y = x->right;
  x->right = y->left;
  y->left = x;
  // 更新高度
  x->height = maxNum(h(x->left), h(x->right)) + 1;
  y->height = maxNum(h(y->left), h(y->right)) + 1;
  return y;
}

/* 右x旋操作
 *      px
 *      |
 *      y
 *    /   \
 *    x    y
 *  /  \
 * lx  ly
 */
AVLNode *rightRotate(AVLNode *y) {
  AVLNode *x = y->left;
  y->left = x->right;
  x->left = y;
  // 更新高度
  x->height = maxNum(h(x->left), h(x->right)) + 1;
  y->height = maxNum(h(y->left), h(y->left)) + 1;
  return x;
}

static AVLNode *insertAVLNode(AVLTree *tree, AVLNode *node, Element elem) {
  if (node == NULL) {
    ++tree->count;
    return createAVLNode(elem);
  }

  if (elem > node->elem) {
    node->right = insertAVLNode(tree, node->right, elem);
  } else if (elem < node->elem) {
    node->left = insertAVLNode(tree, node->left, elem);
  } else {
    return node;
  }

  node->height = maxNum(h(node->left), h(node->right)) + 1;

  int balance = getBalance(node);
  // L
  if (balance > 1) {
    // LR
    if (elem > node->left->elem) {
      node->left = leftRotate(node);
    }
    // LL
    return rightRotate(node);
    // R
  } else if (balance < -1) {
    // RL
    if (elem < node->right->elem) {
      node->right = rightRotate(node);
    }
    // RR
    return leftRotate(node);
  }
  return node;
}

// insert
void insertAVLTree(AVLTree *tree, Element elem) {
  if (tree) {
    tree->root = insertAVLNode(tree, tree->root, elem);
  }
}

// create node
AVLNode *createAVLNode(Element elem) {
  AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));

  if (node == NULL) {
    printf("node malloc failed!\n");
    return NULL;
  }

  node->left = node->right = NULL;
  node->elem = elem;
  node->height = 1;

  return node;
}

static AVLNode *deleteAVLNode(AVLTree *tree, AVLNode *node, Element elem) {
  AVLNode *tmp;
  if (node == NULL) {
    return NULL;
  }

  if (elem > node->elem) {
    node->right = deleteAVLNode(tree, node->right, elem);
  } else if (elem < node->elem) {
    node->left = deleteAVLNode(tree, node->left, elem);
  } else {
    if (node->left == NULL || node->right == NULL) {
      tmp = node->left ? node->left : node->right;
      // 0
      if (tmp == NULL) {
        free(node);
        --tree->count;
        return NULL;
        // 1
      } else {
        node->elem = tmp->elem;
        node->left = tmp->left;
        node->right = tmp->right;
        free(tmp);
        --tree->count;
      }
    } else {
      tmp = node->left;
      while (tmp->right) {
        tmp = tmp->right;
      }
      node->elem = tmp->elem;
      node->left = deleteAVLNode(tree, node->left, tmp->elem);
    }
  }
  node->height = maxNum(h(node->left), h(node->right)) + 1;

  int balance = getBalance(node);
  // L
  if (balance > 1) {
    // LR
    if (getBalance(node->left) < 0) {
      node->left = leftRotate(node);
    }
    // LL
    return rightRotate(node);
    // R
  } else if (balance < -1) {
    // RL
    if (getBalance(node->right) > 0) {
      node->right = rightRotate(node);
    }
    // RR
    return leftRotate(node);
  }

  return node;
}

/*
 * 1. 按照二叉树搜索树的规则，递归找到elem
 * 2. 判断这个节点的度
 *  2.1 如果度为1，用父节点接收存在的子树
 *  2.2 如果度为0，直接删除，父节点接收一个NULL指针
 *  2.3
 * 如果度为2，找到这个节点的前驱或者后继，用这个节点的值替换度为2的节点，转成删除前驱或者后继
 * 3. 归的过程中，找失衡节点
 * 4. 根据LL LR RL RR进行旋转
 */
void deleteAVLTree(AVLTree *tree, Element elem) {
  if (tree) {
    tree->root = deleteAVLNode(tree, tree->root, elem);
  }
}
