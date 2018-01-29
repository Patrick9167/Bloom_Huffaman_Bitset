struct bitset
{
  unsigned int *set;
  int size;
};
typedef struct bitset bs;

struct bitset * bitset_new(int size);

int bitset_lookup(struct bitset * this, int item);

int bitset_add(struct bitset * this, int item);

int bitset_remove(struct bitset * this, int item);

void bitset_union(struct bitset * dest, struct bitset * src1,
                  struct bitset * src2 );

void bitset_intersect(struct bitset * dest, struct bitset * src1,
                      struct bitset * src2);

void print(struct bitset * this);
