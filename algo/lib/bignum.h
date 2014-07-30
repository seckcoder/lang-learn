#ifndef BIGNUM_H
#define BIGNUM_H

#include <ostream>

#ifndef M
#define M 100000
#endif

typedef unsigned char uint8;

std::ostream &operator<<(std::ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

class Bignum {
 public:
  uint8 v[M];
  int len;

  Bignum() {
    for (int i = 0; i < M; i++) {
      v[i] = 0;
    }
    len = 1;
  }
  int addv(int i, int a) {
    a += v[i];
    v[i] = a % 10;
    return a / 10;
  }
  int multv(int i, int cv, int c) {
    cv *= v[i];
    cv += c;
    v[i] = cv % 10;
    return cv / 10;
  }
  Bignum &operator+=(int c) {
    int i = 0;
    while (c != 0) {
      c = addv(i, c);
      i += 1;
    }
    len = std::max(len, i);
    return (*this);
  }
  Bignum &operator*=(const int constv) {
    int carry = 0;
    int i = 0;
    for (i = 0; i < len; i++) {
      carry = multv(i, constv, carry);
    }
    while (carry != 0) {
      carry = addv(i, carry);
      i += 1;
    }
    len = std::max(len, i);
    return (*this);
  }
  Bignum &operator+=(const Bignum &n1) {
    int c = 0;
    int i;
    for (i = 0; i < std::min(n1.len, len); i++) {
      c = addv(i, n1.v[i] + c);
    }
    while (i < n1.len) {
      c = addv(i, n1.v[i] + c);
      i += 1;
    }
    while (c != 0) {
      c = addv(i, c);
      i += 1;
    }
    len = std::max(len, i);
    return *this;
  }
  friend std::ostream &operator<<(std::ostream &os, const Bignum &n) {
    for (int i = n.len - 1; i >= 0; i--) {
      os << n.v[i];
    }
    return os;
  }
};

#endif
