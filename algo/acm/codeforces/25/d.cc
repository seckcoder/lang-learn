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

#define N 1001
#define WHITE 0
#define GRAY 1
#define BLACK 2
vector<int> adjs[N];
uint8 color[N];
int degree[N];
int n;
vector<int> conn_comps;
//vector<std::pair<int, int> > tree_edges;
vector<std::pair<int, int> > back_edges;

void dfs_visit(int u, int pre) {
  color[u] = GRAY;
  for (int i = 0; i < adjs[u].size(); i++) {
    int v = adjs[u][i];
    if (color[v] == WHITE) {
      /*tree_edges.push_back(std::pair<int, int>(std::min(u, v),
                                               std::max(u, v)));*/
      dfs_visit(v, u);
    } else if (color[v] == GRAY && v != pre) {
      // if v == pre, u->v is back edge, but v->u is tree edge, we shouldn't
      // consider this.
      back_edges.push_back(std::pair<int, int>(std::min(u, v),
                                               std::max(u, v)));
    }
  }
  color[u] = BLACK;
}
void dfs() {
  for (int u = 1; u <= n; u++) {
    if (degree[u] == 0 && color[u] == WHITE) {
      conn_comps.push_back(u);
      dfs_visit(u, 0);
    }
  }
  for (int u = 1; u <= n; u++) {
    if (color[u] == WHITE) {
      conn_comps.push_back(u);
      dfs_visit(u, 0);
    }
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int i = 0; i < n-1; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    adjs[a].push_back(b);
    adjs[b].push_back(a);
    degree[a] += 1;
    degree[b] += 1;
  }

  dfs();
  cout << conn_comps.size() - 1 << endl;
  assert(back_edges.size() >= conn_comps.size() - 1);
  for (int i = 0; i < conn_comps.size()-1; i++) {
    printf("%d %d %d %d\n", back_edges[i].first, back_edges[i].second,
           conn_comps[i], conn_comps[i+1]);
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
