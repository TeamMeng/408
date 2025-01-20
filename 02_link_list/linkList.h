#ifndef LINKLIST_H
#define LINKLIST_H

// 单向链表，带头节点的表头

typedef int Element;

// Node
typedef struct Node {
  Element elem;
  struct Node *next;
} Node;

// list struct
typedef struct {
  Node head;
  int len;
} linkList;

// create
linkList *createdLinkList();

// release
void releaseLinkList(linkList *list);

// insert
int insertLinkList(linkList *list, int pos, Element elem);

// delete node
int deleteLinkList(linkList *list, Element e);

// show
void showLinkList(linkList *list);

#endif
