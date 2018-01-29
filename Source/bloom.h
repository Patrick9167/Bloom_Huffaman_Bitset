struct bloom
{
  unsigned int *data;
  int size;
};
typedef struct bloom bl;

struct bloom * bloom_new(int size);

int bloom_lookup(struct bloom * this, char * item);

void bloom_add(struct bloom * this, char * item);

void bloom_union(struct bloom * dest, struct bloom * src1, struct bloom * src2 );

void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2 );

int hash_one (char * item);

int hash_two (char * item);

// void print(struct bloom * this);
