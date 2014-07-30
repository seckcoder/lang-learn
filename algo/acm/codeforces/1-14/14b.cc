//#define SECK_DEBUG

#include <iostream>
#include <vector>
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

void intersect(int ai, int bi, int &a, int &b) {
  a = std::max(a, ai);
  b = std::min(b, bi);
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, x0;
  scanf("%d %d", &n, &x0);
  int a = 0, b = 1000;
  bool impossible = false;
  for (int i = 0; i < n; i++) {
    int ai, bi;
    scanf("%d %d", &ai, &bi);
    if (ai > bi) std::swap(ai, bi);
    if (!impossible) {
      intersect(ai, bi, a, b);
      if (a > b) {
        impossible = true;
      }
    }
  }
  if (impossible) {
    printf("-1\n");
  } else {
    if (a <= x0 && x0 <= b) {
      printf("0\n");
    } else {
      printf("%d\n", std::min(std::abs(a-x0),
                              std::abs(b-x0)));
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
