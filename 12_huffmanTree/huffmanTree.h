#ifndef QUICK_UNION_SET_H
#define QUICK_UNION_SET_H

/* Huffman树表示的是树中各节点带权路径最小值
 * 采用顺序存储方式来表示Huffman树
 * 因为n个元素（叶子节点），那么构造Huffman树的总节点个数为2n-1个
 * 树种的0号索引不使用，从1号索引开始存储元素，那么申请2n个
 * */

// Huffman树的节点结构（表中的一项）
typedef struct {
  int weight;
  int lChild, rChild;
  int parent;
} HuffmanNode, *HuffmanTree;

HuffmanTree createHuffmanTree(const int *w, int n);

void releaseHuffmanTree(HuffmanTree tree);

typedef char *HuffmanCode;

HuffmanCode *createHuffmanCode(HuffmanTree tree, int n);

void releaseHuffmanCode(HuffmanCode *codes, int n);

#endif
