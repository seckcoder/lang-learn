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

int n, m;
#define M 25
class Point {
 public:
  uint8 i, j;
  Point():i(-1),j(-1) {}
  Point(uint8 hi, uint8 hj):i(hi), j(hj) {}
  void set(uint8 hi, uint8 hj) {
    i = hi;
    j = hj;
  }
};

bool dp[M][M][M][M];
bool table[M][M];

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); j++) {
      table[i][j] = bool(s[j]-'0');
    }
  }

  int maxp = 0;
#define setTrue(x1, y1, x2, y2) \
  dp[(x1)][(y1)][(x2)][(y2)] = true; \
  maxp = std::max(((x1)-(x2)+(y1)-(y2)+2)<<1, maxp)

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!table[i][j]) {
        setTrue(i, j, i, j);
        for (int xi = 0; xi < i; xi++) {
          for (int xj = 0; xj < j; xj++) {
            if (dp[i-1][j][xi][xj] && dp[i][j-1][xi][xj]) {
              setTrue(i, j, xi, xj);
            }
          }
        }
        for (int xi = 0; xi < i; xi++) {
          if (dp[i-1][j][xi][j]) {
            setTrue(i, j, xi, j);
          }
        }
        for (int xj = 0; xj < j; xj++) {
          if (dp[i][j-1][i][xj]) {
            setTrue(i, j, i, xj);
          }
        }
      }
    }
  }
  cout << maxp << endl;
#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
