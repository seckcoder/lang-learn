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

#define M 100
int n,m; 
int a[M];
int b[M];

bool adjs[M][M];
bool visited[M];
char flag[M+1];

inline bool conflict(int i, int j) {
  if ((a[i] < a[j] && a[j] < b[i] && b[i] < b[j]) ||
      (a[j] < a[i] && a[i] < b[j] && b[j] < b[i]))  {
    return true;
  }
  return false;
}

char flagType[2] = {'i', 'o'};
bool dfs_visit(int u, int flagi) {
  flag[u] = flagType[flagi];
  visited[u] = true;
  for (int v = 0; v < m; v++) {
    if (adjs[u][v]) {
      if (!visited[v]) {
        if (!dfs_visit(v, flagi ^ 1)) {
          return false;
        }
      } else {
        if (flag[v] == flag[u]) {
          //cout << u << " " << v << endl;
          return false;
        }
      }
    }
  }
  return true;
}
bool dfs() {
  for (int i = 0; i < m; i++) {
    if (!visited[i]) {
      if (!dfs_visit(i, 0)) return false;
    }
  }
  return true;
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d", &a[i], &b[i]);
    if (a[i] > b[i]) std::swap(a[i], b[i]);
  }
  for (int i = 0; i < m; i++) {
    for (int j = i+1; j < m; j++) {
      adjs[i][j] = adjs[j][i] = conflict(i, j);
    }
  }
  flag[m] = '\0';
  if (dfs()) {
    printf("%s\n", flag);
  } else {
    printf("Impossible\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
