#include <stdio.h>
#include "address_ordering.h"

void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int *pval = &ival;
  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

int main(int argc, const char *argv[])
{
  // 12345 = 0x00003039
  test_show_bytes(12345);
  // for int data, if 39 is first printed, then it's little endian.
  return 0;
}
