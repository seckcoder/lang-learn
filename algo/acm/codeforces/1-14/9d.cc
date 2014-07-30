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

#define N 36
int64 dp[N][N];
int64 eqh[N];
int64 e2[N];
bool cached[N][N];

int64 dfs(int n, int h) {
  /*if (n < h) {
    return 0;
  } else if (n == 0 && h == 0) {
    return 1;
  } else if (e2[h] - 1 < n) {
    return 0;*/
  if (n == 0 && h == 0) {
    return 1;
  } else if (n == 0 || h == 0) {
    return 0;
  } else if (cached[n][h]) {
    return dp[n][h];
  } else {
    // n >= 2
    int64 ans = 0;
    for (int i = 1; i <= n; i++) {
      int64 tmp = 0;
      // left < h-1
      int64 right = dfs(n-i, h-1);
      int64 left = 0;
      for (int hx = 0; hx <= h-2; hx++) {
        left += dfs(i-1, hx);
      }
      tmp += left * right;
      left = dfs(i-1, h-1);
      right = 0;
      for (int hx = 0; hx <= h-1; hx++) {
        right += dfs(n-i, hx);
      }
      tmp += left * right;
      ans += tmp;
    }
    cached[n][h] = true;
    dp[n][h] = ans;
    return ans;
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, h;
  scanf("%d %d", &n, &h);

  e2[0] = 1;
  for (int i = 1; i <= h; i++) {
    e2[i] = e2[i-1] * 2;
  }
  int64 ans = 0;
  for (int hx = h; hx <= n; hx++) {
    ans += dfs(n, hx);
  }
  cout << ans << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
