#include <stdio.h>
#include "address_ordering.h"
#include <string.h>

void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int *pval = &ival;
  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

void test_show_bytes1() {
  unsigned char ptr[4];
  int a = 12345;
  // set a block of memory with value
  memcpy(ptr, (byte_pointer)&a, sizeof(int));
  show_bytes(ptr, 5);
  memset(ptr, '-', 4);
  show_bytes(ptr, 4);
}


void test_swap_endian() {
  uint32_t x = 0x00123456u;
  show(x);
  show(swap_endian(x));
  uint64_t x64 = 0x0011223344556677ull;
  show(x64);
  show(swap_endian(x64));
}

int main(int argc, const char *argv[])
{

  printf("is little endian? : %d\n", is_little_endian());
  test_swap_endian();


  // 12345 = 0x00003039
  // test_show_bytes(12345);
  // for int data, if 39 is first printed, then it's little endian.
  // test_show_bytes1();
  return 0;
}
