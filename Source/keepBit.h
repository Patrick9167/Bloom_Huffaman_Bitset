#include <stdio.h>
#include <stdlib.h>

struct keepBit {
  char write;
  char* buff;
};
typedef struct keepBit kbit;

void encode(char** codes, FILE* input, FILE* output);
void decode(char** codes, FILE* input, FILE* output);
int determineChar(FILE* input, char** codes, FILE* output);
