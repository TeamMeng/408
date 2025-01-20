#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

linkList *createdLinkList() {
  linkList *list = (linkList *)malloc(sizeof(linkList));

  if (list == NULL) {
    printf("list malloc failed!\n");
    return NULL;
  }

  list->head.next = NULL;
  list->head.elem = 0;
  list->len = 0;

  return list;
}

void releaseLinkList(linkList *list) {
  if (list) {
    // 遍历链表里的每个元素，依次释放
    Node *head = list->head.next;
    while (head) {
      Node *tmp = head;
      head = tmp->next;
      free(tmp);
      --list->len;
    }
    printf("list node is free, list len is %d\n", list->len);
    free(list);
  }
}

int insertLinkList(linkList *list, int pos, Element elem) {
  if (pos < 1 || pos > list->len + 1) {
    printf("insert pos invaild!\n");
    return -1;
  }

  int i = 0;
  Node *head = &list->head;
  // 找到pos - 1的位置，进行插入操作
  while (head && i < pos - 1) {
    ++i;
    head = head->next;
  }

  // head指向了待插入位置的前一个节点
  Node *node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    printf("insert node malloc failed!\n");
    return -1;
  }

  node->elem = elem;

  node->next = head->next;
  head->next = node;

  ++list->len;

  return 0;
}

int deleteLinkList(linkList *list, Element e) {
  Node *node = &list->head;
  while (node && node->next && node->next->elem != e) {
    node = node->next;
  }
  if (node && node->next) {
    Node *tmp = node->next;
    node->next = tmp->next;
    free(tmp);
    list->len -= 1;
  } else {
    printf("%d elem doesn't exists!\n", e);
  }

  return 0;
}

void showLinkList(linkList *list) {
  Node *node = list->head.next;
  while (node) {
    printf("%d ", node->elem);
    node = node->next;
  }
  printf("\nlink list's len is %d\n", list->len);
}
