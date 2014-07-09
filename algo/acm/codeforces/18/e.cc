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

#define N 500
#define M 500
#define Z 26
uint8 flag[N][M];
int dp[N][Z][Z];
int n, m;
int changes[N][Z][Z];

int change(int i, int u, int v) {
  int cnt = 0;
  for (int j = 0; j < m; j+=2) {
    if (flag[i][j] != u) cnt += 1;
  }
  for (int j = 1; j < m; j+=2) {
    if (flag[i][j] != v) cnt += 1;
  }
  return cnt;
}
string changeFlag(int i, int u, int v) {
  string s(m, 'a');
  for (int j = 0; j < m; j+=2) {
    s[j] = 'a' + u;
  }
  for (int j = 1; j < m; j+=2) {
    s[j] = 'a' + v;
  }
  return s;
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      flag[i][j] = s[j] - 'a';
    }
  }
  for (int u = 0; u < Z; u++) {
    for (int v = u+1; v < Z; v++) {
      dp[0][u][v] = change(0, u, v);
      dp[0][v][u] = change(0, v, u);
    }
  }

  for (int i = 1; i < n; i++) {
    for (int u = 0; u < Z; u++) {
      dp[i][u][u] = INT_MAX;
      for (int v = u+1; v < Z; v++) {
        int cuv = change(i, u, v);
        int cvu = change(i, v, u);
        changes[i][u][v] = cuv;
        changes[i][v][u] = cvu;
        dp[i][u][v] = INT_MAX;
        dp[i][v][u] = INT_MAX;
        for (int g = 0; g < Z; g++) {
          for (int h = 0; h < Z; h++) {
            if (g != h) {
              if (g != u && h != v)  {
                dp[i][u][v] = std::min(dp[i-1][g][h] + cuv,
                                       dp[i][u][v]);
              }
              if (g != v && h != u) {
                dp[i][v][u] = std::min(dp[i-1][g][h] + cvu,
                                       dp[i][v][u]);

              }
            }
          }
        }
      }
    }
  }

  int minc = INT_MAX;
  std::pair<int, int> flag_pairs[N];
  for (int u = 0; u < Z; u++) {
    for (int v = u+1; v < Z; v++) {
      if (dp[n-1][u][v] < minc) {
        minc = dp[n-1][u][v];
        flag_pairs[n-1].first = u;
        flag_pairs[n-1].second = v;
      }
      if (dp[n-1][v][u] < minc) {
        minc = dp[n-1][v][u];
        flag_pairs[n-1].first = v;
        flag_pairs[n-1].second = u;
      }
    }
  }

  int total_c = minc;
  for (int i = n-2; i >= 0; i--) {
    int last_u = flag_pairs[i+1].first;
    int last_v = flag_pairs[i+1].second;
    total_c -= changes[i+1][last_u][last_v];
    bool found = false;
    for (int u = 0; u < Z && !found; u++) {
      for (int v = u+1; v < Z; v++) {
        if (dp[i][u][v] == total_c && u != last_u && v != last_v) {
          flag_pairs[i].first = u;
          flag_pairs[i].second = v;
          found = true;
          break;
        }
        if (dp[i][v][u] == total_c && u != last_v && v != last_u) {
          flag_pairs[i].first = v;
          flag_pairs[i].second = u;
          found = true;
          break;
        }
      }
    }
  }

  cout << minc << endl;
  for (int i = 0; i < n; i++) {
    cout << changeFlag(i, flag_pairs[i].first, flag_pairs[i].second) << endl;
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
