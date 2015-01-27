



#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>


int logicalShift(int x, int n) {
  int arith = x >> n;
  int sign = (~(!!n))+1;
  printf("%d\n",sign);
  int shift_num = (32-n) & sign;
  printf("%d\n", arith>>shift_num);
  return 0;
}


void negate() {
  int x = 1<<31;
  /* haha */
  printf("%d\n", x);
}

int isPower2(int x) {
  int mask = ~0;
  return (!(mask ^ (~x + 1)));
}

unsigned float_i2f(int x) {
  unsigned count = 0x4f800000;
  unsigned tmp;
  unsigned abs = x;
  unsigned last = 0;
  if(x < 0){
    count = 0xcf800000;
    abs = -x;
  }
  while(abs){
    tmp = abs;
    abs <<= 1;
    count = count - 0x800000;
    if(tmp & 0x80000000){
      last = (abs & 0x3ff);
      if(last != 0x100){
        count = count + ((abs & 0x100) >> 8);
      }
      return (abs >> 9) + count;
    }
  }
  return 0;
}

int countBits(int x) {
  unsigned int v;  // 32-bit value to find the log2 of 
  const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
  const unsigned int S[] = {1, 2, 4, 8, 16};
  int i;

  register unsigned int r = 0; // result of log2(v) will go here
  for (i = 4; i >= 0; i--) // unroll for speed...
  {
    if (v & b[i])
    {
      v >>= S[i];
      r |= S[i];
    } 
  }
  return r;
}

int main(int argc, const char *argv[]) {
  float_i2f(3);
  return 0;
}
