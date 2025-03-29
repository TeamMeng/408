#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;

static bool inPageTable(queue<int> page_table, int page) {
  while (!page_table.empty()) {
    if (page_table.front() == page) {
      return true;
    }
    page_table.pop();
  }
  return false;
}

int replace_fifo(int *pages, int page_size, int frame_size) {
  int lack = 0;
  queue<int> page_table;

  for (int i = 0; i < page_size; i++) {
    // 判断每一个请求的页号是否在页表中
    if (!inPageTable(page_table, pages[i])) {
      lack++;
      if (page_table.size() == frame_size) {
        page_table.pop();
      }
      page_table.push(pages[i]);
    }
  }

  return lack;
}

void test01() {
  int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int page_size = sizeof(pages) / sizeof(pages[0]);
  int lack = replace_fifo(pages, page_size, 3);
  // 15
  cout << "FIFO lack num: " << lack << endl;
}

void test02() {
  int pages[] = {3, 2, 1, 0, 3, 2, 4, 3, 2, 1, 0, 4};
  int lack = replace_fifo(pages, sizeof(pages) / sizeof(pages[0]), 3);
  // 9
  cout << "FIFO lack num: " << lack << endl;

  lack = replace_fifo(pages, sizeof(pages) / sizeof(pages[0]), 4);
  // 10
  cout << "FIFO lack num: " << lack << endl;
}

int replace_LRU(int *pages, int page_size, int frame_size) {
  int lack = 0;
  queue<int> page_table;

  for (int i = 0; i < page_size; i++) {
    if (!inPageTable(page_table, pages[i])) {
      if (page_table.size() >= frame_size) {
        page_table.pop();
      }
      ++lack;
      page_table.push(pages[i]);
    } else {
      int elem = pages[i];
      for (int i = 0; i < page_table.size(); i++) {
        int num = page_table.front();
        page_table.pop();
        if (num != elem) {
          page_table.push(num);
        }
      }
      page_table.push(elem);
    }
  }

  return lack;
}

void test03() {
  int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int lack = replace_LRU(pages, sizeof(pages) / sizeof(pages[0]), 3);
  // 9
  cout << "LRU lack num: " << lack << endl;
}

struct clock_table {
  int data;
  int R;
};

static int search_clock(struct clock_table *page_table, int page, int size) {
  for (int i = 0; i < size; i++) {
    if (page_table[i].data == page) {
      return i;
    }
  }
  return -1;
}

int replace_clock(int *pages, int page_size, int frame_size) {
  int lack = 0;
  int pos = 0;

  struct clock_table *page_table = new struct clock_table[frame_size];
  if (page_table == nullptr) {
    return -1;
  }

  for (int i = 0; i < frame_size; i++) {
    page_table[i].data = -1;
    page_table[i].R = -1;
  }

  for (int i = 0; i < page_size; i++) {
    int index = search_clock(page_table, pages[i], frame_size);
    if (index != -1) {
      page_table[index].R = 1;
    } else {
      ++lack;
      if (page_table[pos].R == -1) {
        page_table[pos].data = pages[i];
        page_table[pos].R = 1;
        pos = (pos + 1) % frame_size;
      } else {
        while (1) {
          if (page_table[pos].R == 0) {
            page_table[pos].data = pages[i];
            page_table[pos].R = 1;
            pos = (pos + 1) % frame_size;
            break;
          } else {
            page_table[pos].R = 0;
            pos = (pos + 1) % frame_size;
          }
        }
      }
    }
  }

  return lack;
}

void test04() {
  int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  int lack = replace_clock(pages, sizeof(pages) / sizeof(pages[0]), 3);
  // 14
  cout << "clock lack num: " << lack << endl;
}

int main(int argc, char const *argv[]) {
  test01();
  test02();
  test03();
  test04();
  return 0;
}
