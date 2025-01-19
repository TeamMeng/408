#include "seqList.h"

int main(int argc, char *argv[]) {
  Seqlist *seq = createSeqList(5);

  for (int i = 1; i <= 5; ++i) {
    insertSeqList(seq, i, i);
  }
  showSeqList(seq);

  // insert valid pos
  insertSeqList(seq, 2, 10);
  showSeqList(seq);

  // insert invalid pos
  insertSeqList(seq, 8, 20);

  // delete valid pos
  deleteSeqList(seq, 3);
  showSeqList(seq);

  releaseSeqList(seq);

  return 0;
}
