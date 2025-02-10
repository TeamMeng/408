#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

/* 将x进行左旋，将左、右、父节点进行更新
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 */
static void leftRotate(RBTree *tree, RBNode *x) {
  RBNode *y = x->right;
  x->right = y->left;
  if (y->left) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent) {
    if (x->parent->left == x) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
  } else {
    tree->root = y;
  }
  y->left = x;
  x->parent = y;
}

/* 将y进行左旋，将左、右、父节点进行更新
 *           py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 * */
static void rightRotate(RBTree *tree, RBNode *y) {
  RBNode *x = y->left;
  y->left = x->right;
  if (x->right) {
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent) {
    if (y->parent->right == y) {
      y->parent->right = x;
    } else {
      y->parent->left = x;
    }
  } else {
    tree->root = x;
  }
  x->right = y;
  y->parent = x;
}

RBTree *createRBTree() {
  RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
  tree->root = NULL;
  tree->count = 0;
  return tree;
}

/* 1. 插入节点，如果父节点是黑色的，那么就不用调整
 * 2. 如果父节点是红色，就出现红红现象
 * 2.1 叔叔节点是红色：
 * 		重新调整颜色（g->红，p-》黑，u-》黑），g节点当做新节点，再次循环判断
 * 2.2 叔叔节点是黑色：
 * 		2.2.1 cur是左孩子，par是左孩子
 * 			g右旋，g-》红，p-》黑
 * 		2.2.2 cur是右孩子，par是右孩子
 * 			g左旋，g-》红，p-》黑
 * 		2.2.3 cur是右孩子，par是左孩子
 * 			p左旋，cur和par交换，然后重复2.2.1
 * 		2.2.4 cur是左孩子，par是右孩子
 * 			p右旋，cur和par交换，然后重复2.2.2
 * */
static void insertFixUp(RBTree *tree, RBNode *node) {
  RBNode *parent, *grandParent;
  RBNode *uncle;
  RBNode *tmp;

  parent = node->parent;
  while (parent && parent->color == RED) {
    // 找到祖父节点，根据祖父节点和父节点的关系，确定uncle节点
    grandParent = parent->parent;
    if (parent == grandParent->left) {
      uncle = grandParent->right;
    } else {
      uncle = grandParent->left;
    }
    if (uncle && uncle->color == RED) {
      uncle->color = BLACK;
      parent->color = BLACK;
      grandParent->color = RED;
      node = grandParent;
      parent = node->parent;
      continue;
    }
    if (grandParent->left == parent) { // L
      if (parent->right == node) {     // R
        leftRotate(tree, parent);
        tmp = parent;
        parent = node;
        node = tmp;
      }
      // LL
      rightRotate(tree, grandParent);
      grandParent->color = RED;
      parent->color = BLACK;
    } else {                      // R
      if (parent->left == node) { // L
        rightRotate(tree, parent);
        tmp = parent;
        parent = node;
        node = tmp;
      }
      // RR
      leftRotate(tree, grandParent);
      grandParent->color = RED;
      parent->color = BLACK;
    }
  }
  tree->root->color = BLACK;
}

// 创建一个红黑树的节点，默认创建的节点颜色是红色，父、子都是NULL
static RBNode *createRBNode(keyType key) {
  RBNode *node = (RBNode *)malloc(sizeof(RBNode));
  node->left = node->right = node->parent = NULL;
  node->key = key;
  node->color = RED;
  return node;
}

void insertRBTree(RBTree *tree, keyType key) {
  // 1. 先创建一个红色节点
  RBNode *node = createRBNode(key);
  // 2. 根据二叉搜索树的规则找到待插入的节点
  RBNode *cur = tree->root;
  RBNode *pre = NULL;
  while (cur) {
    pre = cur;
    if (key < cur->key) {
      cur = cur->left;
    } else if (key > cur->key) {
      cur = cur->right;
    } else {
      printf("Key: %d have exist!\n", key);
      return;
    }
  }
  // 3. 若是根节点，更新tree，否则接入红黑树
  node->parent = pre;
  if (pre) {
    if (key < pre->key) {
      pre->left = node;
    } else {
      pre->right = node;
    }
  } else {
    tree->root = node;
    tree->root->color = BLACK;
    tree->count++;
    return;
  }
  // 4. 修正红黑树（修复红红节点）
  insertFixUp(tree, node);
  tree->count++;
}

void printRBTree(RBNode *node, int key, int dir) {
  if (node) {
    if (dir == 0) {
      printf("%d[%c] is root\n", node->key, (node->color == RED) ? 'R' : 'B');
    } else {
      printf("%d[%c] is %d's %s\n", node->key, (node->color == RED) ? 'R' : 'B',
             key, (dir == 1) ? "right child" : "left child");
    }
    printRBTree(node->left, node->key, -1);
    printRBTree(node->right, node->key, 1);
  }
}

static void destoryRBNode(RBTree *tree, RBNode *node) {
  if (node) {
    destoryRBNode(tree, node->left);
    destoryRBNode(tree, node->right);
    free(node);
    --tree->count;
  }
}

void releaseRBTree(RBTree *tree) {
  if (tree) {
    destoryRBNode(tree, tree->root);
    printf("tree's free, tree's count is %d\n", tree->count);
    free(tree);
  }
}
