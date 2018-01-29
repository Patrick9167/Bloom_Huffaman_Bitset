#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"
#include <math.h>


struct bitset * bitset_new(int size)
{
bs *new;
new = malloc(sizeof(bs));
new->size=size;
new->set =calloc(size/(int)sizeof(int), (int)sizeof(int));  //8 lements of 4 bytes = 256 bits
return new;
}

int bitset_lookup(struct bitset * this, int item)
{
  int bitRef = item/32;                                //locate element
  if(bitRef > 8 || bitRef<0)
    return -1;

  int bitNum = item%32;                                //bit number in element
  int bit = this->set[bitRef];
  bit = bit >> (31-bitNum);
  bitRef = bit&1;                                      //check bit state

  if(bitRef==1)
    return 1;
  else
    return 0;
}

int bitset_add(struct bitset * this, int item)
{
  if(bitset_lookup(this, item)==-1)
    return 0;

  int bitRef = item/32;
  int bitNum = item%32;
  int bit = (this->set[bitRef]);
  int mask = 1 << (31-bitNum);                        //create mask to set bit
  bit = bit|mask;

  this->set[bitRef] = bit;

  return 1;

}

int bitset_remove(struct bitset * this, int item)
{
  if(bitset_lookup(this, item)==-1)
    return 0;

  int bitRef = item/32;
  int bitNum = item%32;

  int bit = (this->set[bitRef]);
  int mask = 1 << (31-bitNum);                        //mask with specific bit set
  mask = ~mask;                                       //invert bits to & mask with element
  bit = bit&mask;

  this->set[bitRef] = bit;
  return 1;
}


void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2 )
{
  int i =0;
  while(i<8)
  {
    dest->set[i]|=src1->set[i];                       //set all set bits from both strings
    dest->set[i]|=src2->set[i];                       //in new bitset
    i++;
  }
}

void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
  int i =0;
  while(i<8)
  {
    dest->set[i]|=src1->set[i];                       //set all set bits from string 1
    dest->set[i]&=src2->set[i];                       //& with second string to get similar bits
    i++;
  }
}

void print(struct bitset * this)
{
  int item = 0;
  while(item<256)                                      //run through all characters and
  {                                                    //check if in the bitset and print if so
    if(bitset_lookup(this, item)==1 &&item != 10)
    {
      char c = item;
      printf("%c", c);
      printf(", ");
    }
    item++;
  }
  printf("\n");
}
