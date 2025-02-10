#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int cnt;

unsigned int fib01(unsigned int n) {
  ++cnt;
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  return fib01(n - 1) + fib01(n - 2);
}

void test01() {
  clock_t start = clock();
  unsigned int x = fib01(50);
  clock_t end = clock();
  printf("cost time: %fs. fib01 = %u, cnt = %d\n",
         (double)(end - start) / CLOCKS_PER_SEC, x, cnt);
}

static unsigned int *memo1;

unsigned int fib02(unsigned int n) {
  ++cnt;
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  if (memo1[n] == -1) {
    memo1[n] = fib02(n - 1) + fib02(n - 2);
  }
  return memo1[n];
}

void test02() {
  cnt = 0;
  int n = 50;
  memo1 = (unsigned int *)malloc(sizeof(unsigned int) * (n + 1));
  for (int i = 0; i <= n; ++i) {
    memo1[i] = -1;
  }
  clock_t start = clock();
  unsigned int x = fib02(n);
  clock_t end = clock();
  printf("cost time: %fs. fib02 = %u, cnt = %d\n",
         (double)(end - start) / CLOCKS_PER_SEC, x, cnt);
}

unsigned int fib03(unsigned int n) {
  unsigned int *memo = (unsigned int *)malloc(sizeof(unsigned int) * (n + 1));
  memo[0] = 0;
  memo[1] = 1;

  for (int i = 2; i <= n; ++i) {
    memo[i] = memo[i - 1] + memo[i - 2];
  }

  unsigned int ans = memo[n];
  free(memo);

  return ans;
}

void test03() {
  clock_t start = clock();
  unsigned int x = fib03(50);
  clock_t end = clock();
  printf("cost time: %fs. fib03 = %u\n", (double)(end - start) / CLOCKS_PER_SEC,
         x);
}

int main(int argc, char *argv[]) {
  test01();
  test02();
  test03();
  return 0;
}
