
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <set>
#include <cstdio>
#include <climits>
#include <functional>


using namespace std;

#define int64 long long int

#define N 105

int m, n;
// dp with range
int minCoins[N][N][N];

class Edge {
 public:
  int t; // id
  int v; // alternative price
  Edge() {}
  Edge(int ht, int hv) : t(ht), v(hv) {}
};
class NodeInfo {
 public:
  int p; // price
  int l; // level
  int x; // alternatives
  vector<Edge> edges;
};

NodeInfo nodes[N];

int dfs(int k, int lmin, int lmax) {
  if (minCoins[k][lmin][lmax] > 0) {
    return minCoins[k][lmin][lmax];
  } else {
    minCoins[k][lmin][lmax] = nodes[k].p;
    for (int i = 0; i < nodes[k].edges.size(); i++) {
      int dest_id = nodes[k].edges[i].t;
      int dest_l = nodes[dest_id].l;
      int new_lmin = std::min(dest_l, lmin);
      int new_lmax = std::max(dest_l, lmax);
      if (new_lmax - new_lmin <= m) {
        minCoins[k][lmin][lmax] = 
            std::min(minCoins[k][lmin][lmax],
                     nodes[k].edges[i].v +
                     dfs(dest_id, new_lmin, new_lmax));
      }
    }
    return minCoins[k][lmin][lmax];
  }
}

int main(int argc, const char *argv[])
{
  //freopen("test.in", "r", stdin);

  scanf("%d %d", &m, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d %d %d",
          &(nodes[i].p),
          &(nodes[i].l),
          &(nodes[i].x));
    for (int j = 0; j < nodes[i].x; j++) {
      int t, v;
      scanf("%d %d", &t, &v);
      nodes[i].edges.push_back(Edge(t, v));
    }
  }
  printf("%d\n", dfs(1, nodes[1].l, nodes[1].l));
  return 0;
}
