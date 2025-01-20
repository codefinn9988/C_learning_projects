// `https://www.programiz.com/dsa/huffman-coding`
// `https://www.javatpoint.com/huffman-coding-algorithm`
//  original paper`https://www.ias.ac.in/article/fulltext/reso/011/02/0091-0099`
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 50

// define the node in huffman tree.
// The node structure has only a single member to hold the data.
struct MinHNode {
  char item;
  unsigned freq;
  struct MinHNode *left, *right;
};

// min-heap structure
struct Minheap {
  unsigned size;
  unsigned capacity;
  struct MinHNode **array;
};
void printArray(int arr[], int n);

// create nodes

int main() {
  printf("hello world");
  return 0;
}
