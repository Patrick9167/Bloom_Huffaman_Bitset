#include <stdio.h>
#include <stdlib.h>

struct huffnode {
  int freq;
  int is_compound;
  struct huffnode * left;
  struct huffnode * right;
  unsigned char c;
};
typedef struct huffnode huff;

struct huffnode ** create_node_tree(int * freqs, huff ** nodes);

void walk_tree(huff* root, char* encoding, char** list);

void sort_tree(struct huffnode ** nodes, int size);

huff** build_tree(huff** nodes, int size);

huff* remove_smallest(struct huffnode ** list, int size);
