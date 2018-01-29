#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"
#include <math.h>


struct bloom * bloom_new(int size)
{
  bl *new;
  new = malloc(sizeof(bl));
  new->size = size;
  new->data = calloc(20000 ,(int)sizeof(int));     //elements are 4 bytes, 2000 elements is an arbitrary number
  return new;

};

int bloom_lookup(struct bloom * this, char * item)
{
  int hitem = hash_one(item);             //first hash
  int hitwo = hash_two(item);             //second hash
  int bitRef = hitem/32;                  //array index
  int index2 = hitwo/32;
  if(bitRef > 20000 || bitRef<0 || index2 > 20000 || index2<0)
    return -1;

  int bitNum = hitem%32;                  //number of bit within 4 byte slot
  int bit = this->data[bitRef];
  bit = bit >> (31-bitNum);               //isolate bit
  bitRef = bit&1;

  bitNum = hitwo%32;                      //repeat for 2nd hash
  bit = this->data[index2];
  bit = bit >> (31-bitNum);
  index2 = bit&1;

    if(bitRef==1 && index2==1)            //if both hashed values are present
      return 1;
    else
      return 0;
}

void bloom_add(struct bloom * this, char * item)
{
  if(bloom_lookup(this, item)!=-1 && bloom_lookup(this, item)!=1)
  {
    //printf("%s\n", item);
    int hitem = hash_one(item);
    int hitwo = hash_two(item);

    int bitRef = hitem/32;                //add first hashed value
    int bitNum = hitem%32;
    int bit = (this->data[bitRef]);
    int mask = 1 << (31-bitNum);
    bit = bit|mask;

    this->data[bitRef] = bit;

    bitRef = hitwo/32;                    //add second hash value
    bitNum = hitwo%32;
    bit = (this->data[bitRef]);
    mask = 1 << (31-bitNum);
    bit = bit|mask;

    this->data[bitRef] = bit;


  };
};

void bloom_union(struct bloom * dest, struct bloom * src1, struct bloom * src2 )
{
  int i=0;
  while(i<2000)
  {
    dest->data[i]|=src1->data[i];
    dest->data[i]|=src2->data[i];
    i++;
  }
};

void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2 )
{
  int i=0;
  while(i<2000)
  {
    dest->data[i]|=src1->data[i];
    dest->data[i]&=src2->data[i];
    i++;
  }
};

// SOURCE: djb2
int hash_one (char * item)
{
  unsigned int hash = 5381;
  int i=0;
  char c = item[i];
  while (c)
  {
      hash = 33 * hash ^ (unsigned char)c;        //hash expression 1
      i++;
      c = item[i];
  }

  hash/=10000;
  return hash;
};

int hash_two (char * item)
{
  unsigned int hash = 0;
  int i=0;
  char c = item[i];
  while (c)
  {
      hash = c*2654435761 % (2^32);               //hash expression 2
      hash += hash;
      i++;
      c = item[i];
  }
        //printf("%d\n", hash);
  return hash;
};
