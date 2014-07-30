#define SECK_DEBUG

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

#define N 20 // 3-20
#define T 10 // 1-10
#define H 3 // 0 - 3
int dp[N+1][T+1][H+1][H+1];
bool used[N+1][T+1][H+1][H+1];
int C[H+1][H+1];
int A[H+1];

int f(int n, int t, int hl, int hr, int t0) {
  if (!(2*t+1 <= n && n <= 6*t+1)) return 0;
  //if (n < 2*t+1) return 0;
  if (hl >= H || hr >= H) return 0;
  if (t == 1 || used[n][t][hl][hr]) return dp[n][t][hl][hr];
  int ans = 0;
  for (int ni = 3; ni <= n-2; ni++) {
    for (int ti = 1; ti <= t-ti; ti++) {
    //for (int ti = 1; ti <= t-1; ti++) {
      for (int hi = 0; hi < H; hi++) {
        ans += f(ni, ti, hl, hi, ti) * f(n-ni+1, t-ti, hi, hr, t-ti);
      }
    }
  }
  used[n][t][hl][hr] = true;
  dp[n][t][hl][hr] = ans;
  return ans;
}

int n, t;
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  A[0] = 1;
  for (int i = 1; i <= H; i++) {
    A[i] = i * A[i-1];
  }
  for (int i = 0; i <= H; i++) {
    for (int j = 0; j <= i; j++) {
      C[i][j] = A[i] / (A[j]*A[i-j]);
    }
  }
  cin >> n >> t;
  // t = 1

  for (int len = 3; len <= 7; len++) {
    for (int h1 = 0; h1 < H; h1++) {
      for (int h2 = 0; h2 < H; h2++) {
        for (int i = 2; i <= len-1; i++) {
          for (int h = std::max(h1, h2)+1; h <= H; h++) {
            if (i-2 > h || (len-i-1) > h) {
              dp[len][1][h1][h2] += 0;
            } else {
              dp[len][1][h1][h2] += C[h-h1-1][i-2] * C[h-h2-1][len-i-1];
            }
          }
        }
      }
    }
  }

  // t >= 2
  int ans = 0;
  for (int h1 = 0; h1 < H; h1++) {
    for (int h2 = 0; h2 < H; h2++) {
      ans += f(n, t, h1, h2, 1);
    }
  }
  cout << ans << endl;
  
#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
