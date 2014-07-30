//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
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

template <class T>
T min(T a, T b) {
  return (a<b)?a:b;
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


#define N 1001
#define M 10
//#define MAX_V int64()
const int64 MAX_V = 1e18+1;
int primes[M] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int64 dp[N][M+1];
vector<int> div_vs[N];
int64 pow_v[M][N];
int n;
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int divisor = 2; divisor <= n; divisor += 1) {
    for (int dividend = divisor, q = 1; dividend <= n; dividend += divisor, q+=1) {
      div_vs[dividend].push_back(divisor);
    }
  }
  for (int i = 0; i < M; i++) {
    pow_v[i][0] = 1;
    int64 pre_max_v = MAX_V / primes[i];
    int j;
    for (j = 1; j <= n-1 && pow_v[i][j-1] <= pre_max_v; j++) {
      pow_v[i][j] = pow_v[i][j-1] * primes[i];
    }
  }

  dp[1][0] = 1;

  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= M; j++) {
      int64 cur = MAX_V;
      for (int x = 0; x < div_vs[i].size(); x++) {
        int k = div_vs[i][x]-1; // 1 <= k <= n-1
        int ui = i/(k+1);
        if (pow_v[j-1][k] != 0 &&
            dp[ui][j-1] != 0 &&
            MAX_V / pow_v[j-1][k] > dp[ui][j-1]) {
          cur = min(cur, dp[ui][j-1] * pow_v[j-1][k]);
        }
      }
      if (cur < MAX_V) dp[i][j] = cur;
    }
  }

  int64 res = MAX_V;
  for (int j = 0; j <= M; j++) {
    if (dp[n][j] != 0) res = std::min(dp[n][j], res);
  }
  cout << res << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
