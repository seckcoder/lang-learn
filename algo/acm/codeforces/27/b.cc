//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <list>
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
inline void swap(uint8 &a, uint8 &b) {
  uint8 tmp = b;
  b = a;
  a = tmp;
  return;
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

#define N 51
#define WHITE 0
#define GRAY 1
#define BLACK 2
int n;
bool adjs[N][N];
uint8 color[N];
std::list<uint8> toporder;

void getLostUV(uint8 &lost_u, uint8 &lost_v) {
  for (int i = 1; i <= n; i++) {
    for (int j = i+1; j <= n; j++) {
      if (adjs[i][j] == false && adjs[j][i] == false) {
        lost_u = i;
        lost_v = j;
        return;
      }
    }
  }
}

void dfs_visit(int u) {
  color[u] = GRAY;
  for (int v = 1; v <= n; v++) {
    if (adjs[u][v] && color[v] == WHITE) {
      dfs_visit(v);
    }
  }
  toporder.push_front(u);
  color[u] = BLACK;
}
void topsort() {
  for (int i = 1; i <= n; i++) {
    if (color[i] == WHITE) {
      dfs_visit(i);
    }
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int i = 0; i < n*(n-1)/2 - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    adjs[u][v] = true;
  }
  uint8 lost_u, lost_v;
  getLostUV(lost_u, lost_v);

  topsort();
  for (std::list<uint8>::const_iterator it = toporder.begin();
       it != toporder.end(); it++) {
    if (*it == lost_u) {
      break;
    } else if (*it == lost_v) {
      swap(lost_u, lost_v);
      break;
    }
  }
  cout << lost_u << " " << lost_v << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
