#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int Element;

int binarySearch(const Element *arr, int n, Element target) {
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    int mid = (right - left) / 2 + left;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] > target) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return -1;
}

Element *generateOrderArrya(int n) {
  Element *arr = (Element *)malloc(sizeof(Element) * n);

  if (arr == NULL) {
    printf("arr malloc failed!\n");
    return NULL;
  }

  for (int i = 0; i < n; ++i) {
    arr[i] = i;
  }

  return arr;
}

int main(int argc, char *argv[]) {
  int n = 10000;
  Element *arr = generateOrderArrya(n);

  if (arr == NULL) {
    return -1;
  }

  clock_t start = clock();
  for (int i = 0; i < n; ++i) {
    if (binarySearch(arr, n, n + 10) != -1) {
      printf("error\n");
    }
  }
  clock_t end = clock();

  printf("Time cost: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

  free(arr);

  return 0;
}
