//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <set>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <functional>
#include <climits>
#include <cstdio>
#include <cassert>
//#include "../../../bignum.h"

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;
using std::cerr;
using std::ostream;
using std::istream;


#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

istream &operator>>(istream &is, uint8 &v) {
  int tmp;
  is >> tmp;
  v = (uint8)tmp;
  return is;
}

inline uint8 min(uint8 a, uint8 b) {
  return (a<b)?a:b;
}
inline uint8 max(uint8 a, uint8 b) {
  return (a>b)?a:b;
}

// a,b could be negative
// it always return positive remainder.
int pmod(int a, int b) {
  if (b < 0) {
    return pmod(-a, -b);
  }
  int ret = a % b;
  if (ret < 0) ret += b;
  return ret;
}

#define N 5000
#define M 2001
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
  Bignum(const Bignum &n) {
    (*this) = n;
  }
  Bignum &operator=(const Bignum &n) {
    len = n.len;
    for (int i = 0; i < M; i++) {
      v[i] = n.v[i];
    }
    return (*this);
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
  bool operator>(const Bignum &n) const {
    if (len > n.len) return true;
    if (len < n.len) return false;
    for (int i = len-1; i >= 0; i--) {
      if (v[i] > n.v[i]) return true;
      else if (v[i] < n.v[i]) return false;
    }
    return false;
  }
  friend std::ostream &operator<<(std::ostream &os, const Bignum &n) {
    for (int i = n.len - 1; i >= 0; i--) {
      os << n.v[i];
    }
    return os;
  }
};

int n;

Bignum dp[M];
bool hasWin[M];
Bignum pow2[M];
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  cin >> n;
  pow2[0] += 1;
  for (int i = 1; i < M; i++) {
    pow2[i] = pow2[i-1];
    pow2[i] *= 2;
  }
  Bignum ans;
  for (int i = 0; i < n; i++) {
    string action;
    int  num;
    cin >> action >> num;
    if (action == "win") {
      dp[num] = ans;
      hasWin[num] = true;
    } else if (hasWin[num]) {
      Bignum tmp = pow2[num];
      tmp += dp[num];
      if (tmp > ans) ans = tmp;
    }
  }
  
  cout << ans << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
