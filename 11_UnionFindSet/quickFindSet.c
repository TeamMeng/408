#include "quickFindSet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

QuickFindSet *createQuickFindSet(int n) {
  QuickFindSet *set = (QuickFindSet *)malloc(sizeof(QuickFindSet));
  if (set == NULL) {
    printf("quick find set malloc failed!\n");
    return NULL;
  }

  Element *data = (Element *)malloc(sizeof(Element) * n);
  if (data == NULL) {
    printf("data malloc failed!\n");
    free(set);
    return NULL;
  }

  Element *gruopID = (Element *)malloc(sizeof(Element) * n);
  if (gruopID == NULL) {
    printf("gruopID malloc failed!\n");
    free(set);
    free(data);
    return NULL;
  }

  set->data = data;
  set->groupID = gruopID;
  set->n = n;

  return set;
}

void releaseQuickFindSet(QuickFindSet *set) {
  if (set) {
    if (set->data) {
      free(set->data);
    }
    if (set->groupID) {
      free(set->groupID);
    }
    free(set);
  }
}

void initQuickFindSet(QuickFindSet *set, const Element *data, int n) {
  if (set) {
    for (int i = 0; i < n; ++i) {
      set->data[i] = data[i];
      set->groupID[i] = i;
    }
  }
}

static int findIndex(QuickFindSet *set, Element elem) {
  if (set) {
    for (int i = 0; i < set->n; ++i) {
      if (set->data[i] == elem) {
        return i;
      }
    }
  }

  return -1;
}

int isSameQuickFindSet(QuickFindSet *set, Element a, Element b) {
  if (set) {
    int aIndex = findIndex(set, a);
    int bIndex = findIndex(set, b);
    if (aIndex == -1 || bIndex == -1) {
      return -1;
    }

    return set->groupID[aIndex] == set->groupID[bIndex];
  }
  return -1;
}

// 将元素a和元素b合并，把所有和b元素组信息改为a的组ID
void unionQuickFindSet(QuickFindSet *set, Element a, Element b) {
  int bIndex = findIndex(set, b);
  int aIndex = findIndex(set, a);

  if (bIndex == -1 || aIndex == -1) {
    return;
  }

  int bID = set->data[bIndex];
  for (int i = 0; i < set->n; ++i) {
    if (set->groupID[i] == bID) {
      set->groupID[i] = set->groupID[aIndex];
    }
  }
}
