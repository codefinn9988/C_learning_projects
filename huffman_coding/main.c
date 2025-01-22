/*  Docs
 original paper:
 https://compression.ru/download/articles/huff/huffman_1952_minimum-redundancy-codes.pdf
 https://michaeldipperstein.github.io/huffman.html
 https://en.wikipedia.org/wiki/Huffman_coding
 Shannon–Fano coding = top-down using probability or frequency
 [dbace] -> db | ace ->  d|b  a|ce   -> c|e
 huffman = bottom up using frequency
  */

// without min heap using array
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for huffman tree node
struct Node {
  char character;
  int frequency;
  struct Node *left;
  struct Node *right;
};

// structure to store character codes
struct CharCode {
  char character;
  char code[100]; // store huffman code to that character
};

// create a new node
// function return a pointer of node struct
struct Node *createNode(char character, int frequency) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->character = character;
  node->frequency = frequency;
  node->left = node->right = NULL;
  return node;
}

// build a huffman tree
struct Node *buildHuffmanTree(char *str) {

  // inital count 0 other it put random calue
  int freq[128] = {0};

  // count the frequency of the each character
  for (int i = 0; i < str[i]; i++) {
    freq[str[i]]++;
    // printf(" %s : %d \n", &str[i], freq[str[i]]);
  }

  // create node(char & frequency) and store in nodeArray
  struct Node *nodeArray[128];
  int nodeCount = 0;
  for (int i = 0; i < 128; i++) {
    if (freq[i] > 0) {
      nodeArray[nodeCount++] = createNode(i, freq[i]);
    }
  }
  // print the node array
  // for (int j = 0; j < nodeCount; j++) {
  //   printf("%c: %d\n", nodeArray[j]->character, nodeArray[j]->frequency);
  // }

  while (nodeCount > 1) {
    // first and second
    int min1 = 0, min2 = 1;
    // min1 always should be smaller
    if (nodeArray[min1]->frequency > nodeArray[min2]->frequency) {
      int temp = min1;
      min1 = min2;
      min2 = temp;
    }

    // check remaining node for smallest frequency
    for (int i = 2; i < nodeCount; i++) {
      if (nodeArray[i]->frequency < nodeArray[min1]->frequency) {
        min2 = min1;
        min1 = i;

      } else if (nodeArray[i]->frequency < nodeArray[min2]->frequency) {
        // less than min2 but greater than min1
        min2 = i;
      }
    }

    // Create an internal node that combines the two smallest nodes
    // \0 -> null character
    struct Node *internal = createNode('\0', nodeArray[min1]->frequency +
                                                 nodeArray[min2]->frequency);
    // Link the two smallest nodes as children of the new internal node
    internal->left = nodeArray[min1];
    internal->right = nodeArray[min2];
    // replace one of the entries
    nodeArray[min1] = internal;
    // replace last active node
    nodeArray[min2] = nodeArray[nodeCount - 1];
    // decrease count of active node
    nodeCount--;
    // printf(" %d ", internal->frequency);
  }
  // return root of the huffman tree
  return nodeArray[0];
}

/*
 generate code for each character using recursion.
 *root = current node of huffman tree
 *code = current binary code like '1' or '0' '10001'
 *charCodes = store char and its code eg char = c code = "110";
 *codeCount = Pointer to keep track how many code generated
   */
void generateCodes(struct Node *root, char *code, int depth,
                   struct CharCode *charCodes, int *codeCount) {
  // base case
  if (root == NULL) {
    return;
  }
  //  leaf node check
  if (root->left == NULL && root->right == NULL) {
    // store the character
    charCodes[*codeCount].character = root->character;
    // store the code in .code  like "110" in *code contain = "110\0";
    strcpy(charCodes[*codeCount].code, code);
    // printf("Character: '%c', Code: '%s'\n", charCodes[*codeCount].character,
    //        charCodes[*codeCount].code);
    (*codeCount)++;
    return;
  }
  // 0 for left child
  code[depth] = '0';
  // null character to end of string of code like "0\0"
  code[depth + 1] = '\0';
  // traversing left child
  generateCodes(root->left, code, depth + 1, charCodes, codeCount);

  // 1 for right child
  code[depth] = '1';
  code[depth + 1] = '\0';
  // traversing right child
  generateCodes(root->right, code, depth + 1, charCodes, codeCount);
}

// Encode string and return the encoded result
// *encoded =  char arrary which sotre all result encde string
// like this:  "110111000011100011110001"
void encode(char *str, struct CharCode *charCodes, int codeCount,
            char *encoded) {
  encoded[0] = '\0'; // Initialize empty string
  for (int i = 0; str[i]; i++) {
    for (int j = 0; j < codeCount; j++) {
      if (charCodes[j].character == str[i]) {
        // append in encoded
        strcat(encoded, charCodes[j].code);
        // printf("Encoding character: '%c' -> Code: '%s'\n", str[i],
        //        charCodes[j].code);
        break;
      }
    }
    // printf(" endoded %s\n", &encoded[i]);
  }
}

// decode string using huffman tree
// *root = pointer of root of huffman tree
void decode(char *encoded, struct Node *root) {
  // *current = current root of huffman tree when traversing
  struct Node *current = root;
  printf("Decoded string: ");

  for (int i = 0; encoded[i]; i++) {
    if (encoded[i] == '0') {
      // move to left child
      current = current->left;
    } else {
      // move to right child if e[i] = 1
      current = current->right;
    }

    // check leaf node
    if (current->left == NULL && current->right == NULL) {
      printf("%c", current->character);
      // reset the root for next character
      current = root;
    }
  }
  printf("\n");
}

int main() {
  char str[] = "hello world";
  printf("Original string: %s\n", str);

  // Build Huffman tree
  struct Node *root = buildHuffmanTree(str);
  struct CharCode charCodes[128];
  int codeCount = 0;
  char code[100] = "";

  generateCodes(root, code, 0, charCodes, &codeCount);

  // Print character codes
  printf("\nCharacter codes:\n");
  for (int i = 0; i < codeCount; i++) {
    printf("%c: %s\n", charCodes[i].character, charCodes[i].code);
  }

  // // Encode the string
  char encoded[1000] = ""; // Make sure this is large enough
  encode(str, charCodes, codeCount, encoded);
  printf("\nEncoded string: %s\n", encoded);

  // Decode the same encoded string
  decode(encoded, root);
  return 0;
}
