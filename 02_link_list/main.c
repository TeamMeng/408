#include "linkList.h"

int main(int argc, char *argv[]) {
  linkList *list = createdLinkList();
  for (int i = 1; i <= 5; ++i) {
    insertLinkList(list, i, i);
  }

  showLinkList(list);

  deleteLinkList(list, 3);
  showLinkList(list);

  deleteLinkList(list, 5);
  showLinkList(list);

  deleteLinkList(list, 1);
  showLinkList(list);

  // invalid elem
  deleteLinkList(list, 1);

  releaseLinkList(list);
  return 0;
}
