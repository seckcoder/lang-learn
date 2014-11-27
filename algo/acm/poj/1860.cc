
// 1. Why it's not NP-hard?

#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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


class Edge {
 public:
  int v;
  double r, c;
  Edge() {}
  Edge(int hv, double hr, double hc):v(hv), r(hr), c(hc) {}
};


void addEdge(vector<vector<Edge> > &es, int u, int v, double r, double c) {
  es[u-1].push_back(Edge(v-1, r, c));
}


bool BellmanFord(const vector<vector<Edge> > &es) {
}

bool solve() {
  int n,m;
  double s,v;
  cin >> n >> m >> s >> v;
  vector<vector<Edge> > es(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    double ruv, cuv, rvu, cvu;
    scanf("%d %d %lf %lf %lf %lf", &u, &v, &ruv, &cuv,
          &rvu, &cvu);
    addEdge(es, u, v, ruv, cuv);
    addEdge(es, v, u, rvu, cvu);
  }
  return BellmanFord(es);
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  if (solve()) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
