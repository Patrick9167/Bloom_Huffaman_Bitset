#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/*CREATE array of frequencies*/
huff ** create_node_tree(int * freqs, huff ** nodes)
{

  for(int i =0; i<256; i++)
  {
    nodes[i] = malloc(sizeof(huff));
    nodes[i]->freq = freqs[i];
    nodes[i]->is_compound = 0;
    nodes[i]->c =i;
  }
  return nodes;
}

/*CREATE compound nodes and link them*/
huff** build_tree(huff** nodes, int size)
{
  while(size>1)
  {
    huff *small1, *small2, *compound;

    small1 = nodes[0];
    small2 = nodes[1];

    //combine 2 smallest and compound node
    compound = malloc(sizeof(huff));
    compound->freq = (small1->freq + small2->freq);
    compound->is_compound =1;
    compound->left=small1;
    compound->right=small2;
    compound->c=small2->c;

    nodes[0]=nodes[--size];
    nodes[size]=NULL;
    nodes[1]=nodes[--size];
    nodes[size++]=compound;
    sort_tree(nodes, size);

  }
return nodes;
}

/*SORT tree so the nodes are ordered in increasing frequency*/
void sort_tree(struct huffnode ** nodes, int size)
{
  huff* temp;
  int d;
  for (int i = 1 ; i < size; i++) {
    d = i;

    while ( (d > 0 && nodes[d]->freq < nodes[d-1]->freq))
    {
      temp  = nodes[d];
      nodes[d] = nodes[d-1];
      nodes[d-1] = temp;
      d--;
    }
  }
}

/*WALK through tree assigning codes to each char and add codes to a 
2d array*/
void walk_tree(huff* root, char* encoding, char** list)
{
  if(root->is_compound ==0)
  {
    printf("%c %s", root->c,  ": ");
    list[(int)root->c]=calloc(256, sizeof(char));
    strcpy(list[(int)root->c], encoding);
   printf("%s\n", list[(int)root->c]);
  }
  else
  {
    int index = strlen(encoding);
    encoding[index]='0';
    encoding[index+1]='\0';
    walk_tree(root->left, encoding, list);
    encoding[index]='1';
    encoding[index+1]='\0';
    walk_tree(root->right, encoding, list);
  }
}
