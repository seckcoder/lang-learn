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

#define N 50 
#define M 2500
class Edge {
 public:
  uint8 u, v;
  Edge() {}
  Edge(uint8 hu, uint8 hv): u(hu), v(hv) {}
  friend istream&operator>>(istream &is, Edge &e) ;
  friend ostream&operator<<(ostream &os, const Edge &e);
  bool operator<(const Edge &e) const {
    return (u < e.u) || (u == e.u && v < e.v);
  }
};
istream &operator>>(istream &is, Edge &e) {
  is >> e.u >> e.v;
  if (e.u > e.v) std::swap(e.u, e.v);
  return is;
}

ostream &operator<<(ostream &os, const Edge &e) {
  os << e.u << " " << e.v;
  return os;
}
Edge es[M];
uint8 degree[N+1];
int n, m;
// disjoint set node
class Node {
 public:
  uint8 r;
  uint8 p;
};
Node nodes[N+1];
vector<Edge> added_edges;

void make_set(uint8 i) {
  nodes[i].p = i;
  nodes[i].r = 0;
}

uint8 find_set(uint8 x) {
  if (x != nodes[x].p) {
    nodes[x].p = find_set(nodes[x].p);
  }
  return nodes[x].p;
}

bool union_set(uint8 x1, uint8 x2) {
  uint8 r1 = find_set(x1);
  uint8 r2 = find_set(x2);
  if (r1 != r2) {
    if (nodes[r1].r < nodes[r2].r) {
      nodes[r1].p = nodes[r2].p;
    } else {
      nodes[r2].p = nodes[r1].p;
    }
    return true;
  } else {
    return false;
  }
}

bool isFunnyRing() {
  uint8 root = find_set(1);
  for (uint8 i = 2; i <= n; i++) {
    if (degree[i] != 2 || find_set(i) != root) {
      return false;
    }
  }
  return true;
}

bool solve() {
  for (int i = 1; i <= n; i++) {
    make_set(i);
  }
  for (int i = 0; i < m; i++) {
    degree[es[i].u] += 1;
    degree[es[i].v] += 1;
    union_set(es[i].u, es[i].v);
    if (degree[es[i].u] > 2 ||
        degree[es[i].v] > 2) {
      return false;
    }
  }
  if ( n == 1 ) {
    if (m == 0) {
      added_edges.push_back(Edge(1,1));
    }
    return true;
  }
  // n >= 2
  // connect connected components
  for (uint8 i = 1; i <= n; i++) {
    for (uint8 j = i+1; j<= n && degree[i] < 2; j++) {
      if (degree[j] < 2 && union_set(i, j)) {
        added_edges.push_back(Edge(i, j));
        degree[i] += 1;
        degree[j] += 1;
      }
    }
  }

  // connect endpoints
  // It can be proved that the added edges are lexicographically smallest.
  for (uint8 i = 1; i <= n; i++) {
    for (uint8 j = i+1; j <= n && degree[i] < 2; j++) {
      if (degree[j] < 2) {
        added_edges.push_back(Edge(i, j));
        degree[i] += 1;
        degree[j] += 1;
      }
    }
  }
  return isFunnyRing();
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    cin >> es[i];
  }
  
  if (!solve()) {
    printf("NO\n");
  } else {
    printf("YES\n");
    cout << added_edges.size() << endl;
    for (int i = 0; i < added_edges.size(); i++) {
      cout << added_edges[i] << endl;
    }
  }


#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
