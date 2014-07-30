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

#define N 200

typedef std::pair<uint8, uint8> Edge;


class Vertex {
 public:
  uint8 d;
};
class Graph {
 public:
  Vertex v[N+1];
  vector<uint8> e[N+1];
};
//bool vv[N+1][N+1];
Edge es[N+1];
uint8 n;
Graph g;

void addEdge(const Edge &e) {
  g.e[e.first].push_back(e.second);
  g.e[e.second].push_back(e.first);
}

struct BFSParam {
 public:
  uint8 excluded;
  uint8 d; // diameter
  uint8 v; // vertex at the other end of diameter
};

uint8 d[N+1];
bool visited[N+1];
void bfs(uint8 u, BFSParam &param) {
  std::queue<uint8> q;
  q.push(u);
  g.v[u].d = 0;
  param.d = 0;
  memset(visited, false, sizeof(visited));
  // u-param.excluded 连接两个连通分量，当把visited[param.excluded]设为true
  // 后自然把图分成了两部分。 
  visited[param.excluded] = true;
  visited[u] = true;
  while (!q.empty()) {
    u = q.front();
    q.pop();
    if (g.v[u].d > param.d) {
      param.d = g.v[u].d;
      param.v = u;
    }
    for (int i = 0; i < g.e[u].size(); i++) {
      uint8 v = g.e[u][i];
      if (!visited[v]) {
        g.v[v].d = g.v[u].d + 1;
        q.push(v);
        visited[v] = true;
      }
    }
  }
}

// get diameter of the tree rooted at u. pre is root of u
int diameter(uint8 u, uint8 pre) {
  BFSParam param = {pre, 0, 0};
  bfs(u, param);
  bfs(param.v, param);
  return param.d;
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  cin >> n;
  for (int i = 0; i < n-1; i++) {
    cin >> es[i].first >> es[i].second;
    addEdge(es[i]);
  }

  int ans = 0;
  for (int i = 0; i < n-1; i++) {
    int d1 = diameter(es[i].first, es[i].second);
    if (d1 > 0) {
      int d2 = diameter(es[i].second, es[i].first);
      ans = std::max(d1*d2, ans);
    }
  }
  printf("%d\n", ans);
  //cout << ans << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
