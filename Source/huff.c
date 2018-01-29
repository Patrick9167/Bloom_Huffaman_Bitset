#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.c"
#include "keepBit.c"

int main(int argc, char ** argv)
{
  if ( argc !=5 ) {
    fprintf(stderr, "Useage: huff encode/decode <training filename> <input filename> <output filename>\n");
    exit(1);	    // exit with error code
  }
  FILE * file;
  FILE* input;
  FILE* output;
  unsigned char c;
  int nFreqs=256;
  int freqs[nFreqs];

  //get frequencies with training file
  for(int j=0; j<256; j++)
    freqs[j]=0;
  file = fopen(argv[2], "r");
  assert( file != NULL );
  c = fgetc(file);	// attempt to read a byte
  while( !feof(file) ) {
    freqs[c]++;
    c = fgetc(file);
  }
  fclose(file);
  //Set any chars of frequency 0 to 1
  for(int j=0; j<256; j++)
    if(freqs[j]==0) freqs[j]=1;

  //print frequencies
  for(int j =0; j<256; j++)
  {
    printf("%c %s", j,  ": ");
    printf("%d\n", freqs[j]);
  }

  //create tree using frequencies
  huff** tree;
  tree = malloc(sizeof(huff) * nFreqs);
  tree = create_node_tree(freqs, tree);
  sort_tree(tree, nFreqs);
  tree = build_tree(tree, nFreqs);

  //Get encodings for characters and store them in 2d array
  char* encoding = malloc(256*(sizeof(char)));
  encoding[0]='\0';
  char** codeList= calloc(nFreqs, sizeof(char)*32);
  walk_tree(tree[0], encoding, codeList);

  input = fopen(argv[3], "r");
  output = fopen(argv[4], "w");
  assert( input != NULL);
  assert( output != NULL);

  if(strcmp(argv[1], "encode")==0)
  {
      encode(codeList, input, output);  //encode a plain text file
  }
  else if(strcmp(argv[1], "decode")==0)
  {
    decode(codeList, input, output);    //decode a plain text file
  }

}
