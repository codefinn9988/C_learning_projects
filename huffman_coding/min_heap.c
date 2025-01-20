// docs:  `https://github.com/robin-thomas/min-heap`
// `https://en.wikipedia.org/wiki/Heap_(data_structure)`
// `https://en.wikipedia.org/wiki/Binary_heap`

#include <stdio.h>
#include <stdlib.h>
// macros
#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

// single node
typedef struct node {
  int data;
} node;

// min heap multiple node
typedef struct minHeap {
  int size;
  node *element;
} minHeap;

// Function to initialize the min heap with size = 0
minHeap /*(return type minHeap)*/ initMinHeap() {
  minHeap hp;
  hp.size = 0;
  hp.element = NULL;
  return hp;
}

// swap the nodes
void swap(node *n1, node *n2) {
  node temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

// heapify function make sure it never violated the heap property root
// (node<child nodes)
void heapify(minHeap *hp, int i) {
  // if left is min smallest = left
  int smallest = (LCHILD(i) < hp->size &&
                  hp->element[LCHILD(i)].data < hp->element[i].data)
                     ? LCHILD(i)
                     : i;

  // if right is min smallest = right
  if (RCHILD(i) < hp->size &&
      hp->element[RCHILD(i)].data < hp->element[smallest].data) {
    smallest = RCHILD(i);
  }

  // swap node and check gain in binary tree
  if (smallest != i) {
    swap(&(hp->element[i]), &(hp->element[smallest]));
    heapify(hp, smallest);
  }
}

// build the minHeap
void buildMinHeap(minHeap *hp, int *arr, int size) {
  int i;
  // insert
  for (i = 0; i < size; i++) {
    // if heap has already node
    if (hp->size) {
      hp->element = realloc(hp->element, (hp->size + 1) * sizeof(node));
    } else { // if heap is empty
      hp->element = malloc(sizeof(node));
    }
    node nd;
    nd.data = arr[i];
    // new node is added to new heap element array
    hp->element[(hp->size)++] = nd;
  }
  // check with last leaf node to root
  for (i = (hp->size - 1) / 2; i >= 0; i--) {
    heapify(hp, i);
  }
}

// insert node
void insertNode(minHeap *hp, int data) {
  if (hp->size) {
    hp->element = realloc(hp->element, (hp->size + 1) * sizeof(node));
  } else {
    hp->element = malloc(sizeof(node));
  }
  node nd;
  nd.data = data;
  int i = (hp->size)++;
  while (i && nd.data < hp->element[PARENT(i)].data) {
    // move PARENT node to i
    hp->element[i] = hp->element[PARENT(i)];
    // then update the i
    i = PARENT(i);
  }
  // once correct position is found it  new node
  hp->element[i] = nd;
}
// delete node
void deleteNode(minHeap *hp) {
  if (hp->size) {
    // deleting root node minimum element
    printf("Deleting node %d\n\n", hp->element[0].data);
    // root node is replaced by last element of the heap
    // also decrement the hp size by one
    hp->element[0] = hp->element[--(hp->size)];
    // this doesnot decrease the size of heap only assign
    // hp->element[0] = hp->element[hp->size - 1];
    hp->element = realloc(hp->element, hp->size * sizeof(node));
    heapify(hp, 0);
  } else {
    printf("\n Min Heap is empty \n");
    free(hp->element);
  }
}
// get max node
// i = index of current node start to search for the maximum value
int getMaxNode(minHeap *hp, int i) {
  // check out of bound
  // if curr = leaf node
  if (LCHILD(i) >= hp->size) {
    return hp->element[i].data;
  }
  // else current node has children check maximum
  int l = getMaxNode(hp, LCHILD(i));
  int r = getMaxNode(hp, RCHILD(i));
  if (l >= r) {
    return l;
  } else {
    return r;
  }
}
// clear malloc
void deleteMinHeap(minHeap *hp) {
  // free the min heap;
  free(hp->element);
  hp->element = NULL;
}
// inorder traversal
void inorderTraversal(minHeap *hp, int i) {
  if (hp->size == 0) {
    printf("\nHeap is empty.\n");
    return;
  }
  if (LCHILD(i) < hp->size) {
    inorderTraversal(hp, LCHILD(i));
  }
  printf("%d ", hp->element[i].data);
  if (RCHILD(i) < hp->size) {
    inorderTraversal(hp, RCHILD(i));
  }
}
// preorder traversal
void preorderTraversal(minHeap *hp, int i) {
  if (LCHILD(i) < hp->size) {
    inorderTraversal(hp, LCHILD(i));
  }
  if (RCHILD(i) < hp->size) {
    inorderTraversal(hp, RCHILD(i));
  }
  printf("%d ", hp->element[i].data);
}
// postorder traversal
void postorderTraversal(minHeap *hp, int i) {
  printf("%d ", hp->element[i].data);
  if (LCHILD(i) < hp->size) {
    inorderTraversal(hp, LCHILD(i));
  }
  if (RCHILD(i) < hp->size) {
    inorderTraversal(hp, RCHILD(i));
  }
}

// level order traversal
void levelorderTraversal(minHeap *hp) {
  int i;
  for (i = 0; i < hp->size; i++) {
    printf("%d ", hp->element[i].data);
  }
}

int main() {
  minHeap myHeap = initMinHeap();

  int data[] = {5, 3, 8, 4, 1};
  // build min heap
  buildMinHeap(&myHeap, data, sizeof(data) / sizeof(data[0]));

  printf("Min Heap after building:\n");
  levelorderTraversal(&myHeap);

  printf("\n\nInserting elements:\n");
  insertNode(&myHeap, 2);
  printf("Min Heap after insertion:\n");
  levelorderTraversal(&myHeap);

  printf("\n\nDeleting minimum element:\n");
  deleteNode(&myHeap);
  printf("Min Heap after deletion:\n");
  levelorderTraversal(&myHeap);

  printf("\n\n inorder Traversal\n");
  inorderTraversal(&myHeap, 0);

  printf("\n\n preorder Traversal\n");
  preorderTraversal(&myHeap, 0);

  printf("\n\n post order Traversal\n");
  postorderTraversal(&myHeap, 0);

  printf("\n\n GET max number : %d \n", getMaxNode(&myHeap, 0));

  // clean up memory before exiting
  deleteMinHeap(&myHeap);
  return 0;
}
