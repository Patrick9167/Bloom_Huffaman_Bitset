#include <stdio.h>
#include <stdlib.h>
#include "bloom.c"
#include "bitset.c"
#include <string.h>
int main()
{

  char ans[256];
  printf("bitset or bloom?");
  fgets(ans, 256, stdin);                         //enter choice

  if(ans[1]=='i')
  {
    const int MAX_STRING = 256;                   //bitset
    char test1[MAX_STRING];
    char test2[MAX_STRING];
    printf("Enter expresion>> ");
    //Input expression
    fgets(test1, MAX_STRING, stdin);

    struct bitset *src1 = bitset_new(MAX_STRING); // new bitset - first string


    char charac=0;
    int i =0;

    while(test1[i]!='\0')
    {
      charac = test1[i];
      bitset_add(src1, charac);                   // add characters from string to bitset
      i++;
    }
  //  bitset_remove(src1, 's');
    printf("Enter the second expresion>> ");
    //Input expression
    fgets(test2, MAX_STRING, stdin);

    struct bitset *src2 = bitset_new(MAX_STRING); // new bitset - second string

    charac=0;
    i =0;

    while(test2[i]!='\0')
    {
      charac = test2[i];
       bitset_add(src2, charac);                  // add characters from string to bitset
      i++;
    }
    print(src1);
    print(src2);

    struct bitset *u = bitset_new(MAX_STRING);    //new bitset - union
    bitset_union(u,src1,src2);
    printf("Union: ");
    print(u);

    struct bitset *in = bitset_new(MAX_STRING);   //new bitset - intersection
    bitset_intersect(in,src1,src2);
    printf("Interesection: ");
    print(in);

  }
  else if(ans[1]=='l')
  {
    bl*seen = bloom_new(256);

    FILE* file;
    FILE* fil2;
    file = fopen("AP.txt", "r");
  //  fil2 = fopen("life.txt", "r");                 //read in files



    int count=0;
    char *string = calloc(20, sizeof(char));
    while (count<300)
    {
      fscanf(file, "%s", string);                 //add file 1 content to seen filter
      bloom_add(seen, string);

      ++count;
    }




    bl*written = bloom_new(256);
    count=0;
    while (count<300)
    {
      fscanf(file, "%s", string);
      if(bloom_lookup(seen, string)==1)
      {
        if(bloom_lookup(written, string)!=1)
        {
          printf("%s\n", string);               //add file 2 content to written filter
          bloom_add(written, string);           //if already in seen filter and print
        }
      }

      ++count;
    }
    printf("\n");
  }
}
