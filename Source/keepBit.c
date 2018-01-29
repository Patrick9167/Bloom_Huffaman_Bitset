#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keepBit.h"

void encode(char** codes, FILE* input, FILE* output)
{
  kbit* buffer = malloc(sizeof(kbit));
  buffer->write=0;                        //byte to print
  int i=0;
  int count=0;
  char* code=malloc(256*sizeof(char));    //temp for each char's code
  unsigned char c;
  c = fgetc(input);
  while( !feof(input) ) {

    code=codes[c];                    //get code for character
    //printf("%s %s", code, "");
    while(count< 8 && code[i]!='\0')  //set bits in byte to correspond with code
    {
      if(code[i]=='1') buffer->write |= 0x1;
      count++;
      if(count!=8)buffer->write <<= 1;
      i++;
    }

    if(count==8)                      //if byte filled, print it to output file
    {                                 //then reset byte
      fputc(buffer->write, output);
      buffer->write=0;
      count=0;
    }
    if(code[i]=='\0')                 //if at end of code, get next character
    {                                 //from input
      i=0;
      c = fgetc(input);
    }
  }
}

/*CHECK string from encoded file with codes, return char if match*/
int loopCodes(char* read, char** codes)
{
  for(int i=0; i<256; i++)
  {
    if(strcmp(read, codes[i])==0)
      return i;
  }
  return -1;
}


void decode(char** codes, FILE* input, FILE* output)
{
  int i=0;
  int j=0;
  kbit* buffer = malloc(sizeof(kbit));
  buffer->buff=malloc(256*sizeof(char));     //temp string for codes from encoded file
  int check=0;
  unsigned char c;
  buffer->write=fgetc(input);                //next byte
  int mask = 0x10000000;

  while(!feof(input))
  {
    int temp = buffer->write & mask;        //isolate next bit
    buffer->write <<= 1;
    i++;
    temp >>=7;
    if(temp==0) buffer->buff[j++]='0';      //add next bit to code temp string
    else buffer->buff[j++]='1';
                                            //check temp to see if its a valid
    check = loopCodes(buffer->buff, codes); //code

    if(check>=0 && check<256)               //If it is valid, print to output
    {                                       //and reset temp string
      c = check;
      fputc(c, output);
      j=0;
      buffer->buff=malloc(256*sizeof(char));
    }
    if(i>7)                                 //if the byte is empty
    {                                       // get next byte
      i=0;
      buffer->write = fgetc(input);
    }

  }
}
