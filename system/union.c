

#include <stdio.h>


struct Record {
  long value2;
  double value;
  char tag[3];
};

struct Node {
  int ref_count;
  struct Record record;
  // char mix[12];
  union {
    double d;
    char string[12];
  } mix;
};


int main() {
  struct Node my_node;
  printf("%zu \n%zu %zu %zu",
      sizeof(my_node),
      sizeof(my_node.ref_count),
      sizeof(my_node.record),
      sizeof(my_node.mix)
      );
  return 0;
}
