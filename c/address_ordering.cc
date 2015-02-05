#include <stdio.h>
#include "address_ordering.h"


// Notes:
//
// endian is about the ordering of bytes.
// Least significant byte first -> Little Endian
// endian difference is present in both register and memory. When data is copied
// from memory to register, the byte in lower order is copied to the lower order
// of the register.
//
void show_bytes(byte_pointer start, size_t len) {
  // enumerate: low address -> high address
  for (size_t i = 0; i < len; i++)
    printf(" %.2x", start[i]);
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
  show_bytes((byte_pointer) &x, sizeof(void *));
}

int is_little_endian() {
  uint32_t x = 0x01234567;
  byte_pointer ptr = (byte_pointer) &x;
  return (uint8_t) ptr[0] == 0x67;
}

void swap_endian(byte_pointer p1, byte_pointer p2, uint8_t len) {
  // swap bytes in lower order with bytes in higher order
  for (uint8_t i = 0; i < len; i++) {
    p2[len-i-1] = p1[i];
  }
}

uint32_t swap_endian(uint32_t x) {
  // the same idea, just use bit operation to optimize it.
  return ((x & 0x000000ff) << 24u) +
         ((x & 0x0000ff00) << 8u) +
         ((x & 0x00ff0000) >> 8u) +
         ((x & 0xff000000) >> 24u);
}

uint64_t swap_endian(uint64_t x) {
  uint64_t ans;
  swap_endian(byte_pointer(&x), byte_pointer(&ans), uint8_t(sizeof(ans)));
  return ans;
}
