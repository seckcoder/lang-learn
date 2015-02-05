#include <stdint.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) ;
template <class T>
void show(T x) {
  show_bytes(byte_pointer(&x), sizeof(x));
}
void show_int(int x) ;
void show_float(float x) ;
void show_pointer(void *x) ;
int is_little_endian(); // decides whether the machine is little endian
void swap_endian(byte_pointer p1, byte_pointer p2, uint8_t len);
uint32_t swap_endian(uint32_t);
uint64_t swap_endian(uint64_t);
