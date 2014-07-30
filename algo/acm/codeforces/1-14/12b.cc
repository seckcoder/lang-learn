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

int getDigits(int n, char digits[]) {
  int k = 0;
  while (n != 0) {
    digits[k] = '0' + n % 10;
    n = n / 10;
    k += 1;
  }
  digits[k] = '\0';
  return k;
}

int getNum(const vector<uint8> &digits) {
  int n = 0;
  for (int i = 0; i < digits.size(); i++) {
    n = n * 10 + digits[i];
  }
  return n;
}
// shift left for 1
template <class T>
bool shift1(vector<T> &vec) {
  assert(vec.size() > 0);
  std::reverse(vec.begin(), vec.begin()+1);
  std::reverse(vec.begin()+1, vec.end());
  std::reverse(vec.begin(), vec.end());
  return (vec[0] != 0) ;
}
void smallestShuffle(int n, char digits[]) {
  if (n == 0) {
    digits[0] = '0';
    digits[1] = '\0';
  } else {
    int l = getDigits(n, digits);
    std::sort(digits, digits+l);
    int k = 0;
    while (k < l && digits[k] == '0') {
      k += 1;
    }
    std::swap(digits[0], digits[k]);
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  char m[10];
  scanf("%d %s", &n, m);
  char digits[10];
  smallestShuffle(n, digits);
  if (strcmp(digits, m) == 0) {
    printf("OK\n");
  } else {
    printf("WRONG_ANSWER\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
