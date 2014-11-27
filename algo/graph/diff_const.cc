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
  int u,v, w;
};


void printEdges(const vector<Edge> &es) {
  for (int i = 0; i < es.size(); i++) {
    printf("%d %d %d\n", es[i].u, es[i].v, es[i].w);
  }
}

void initializeBellmanFord(vector<int> &d) {
  std::fill(d.begin(), d.end(), 0);
}
void relax(const Edge &e, vector<int> &d) {
  if (d[e.v] > d[e.u] + e.w) {
    d[e.v] = d[e.u] + e.w;
  }
}
bool BellmanFord(const vector<Edge> &es, vector<int> &d) {
  initializeBellmanFord(d);
  for (int i = 1; i < d.size(); i++) {
    for (int j = 0; j < es.size(); j++) {
      relax(es[j], d);
    }
  }
  for (int j = 0; j < es.size(); j++) {
    if (d[es[j].v] > d[es[j].u] + es[j].w) {
      return false;
    }
  }
  return true;
}

vector<Edge> es;
vector<int> d;
int n,m;

void solve() {
  while (scanf("%d %d", &n, &m) != EOF) {
    es.resize(m);
    //es.resize(n+m);
    d.resize(n+1);
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d", &es[i].v, &es[i].u, &es[i].w);
    }
    /*for (int i = 1, j = m; i <= n; i++, j++) {
      es[j].u = 0;
      es[j].v = i;
      es[j].w = 0;
    }*/
    if (BellmanFord(es, d)) {
      for (int i = 1; i < d.size(); i++) {
        cout << d[i] << " ";
      }
      cout << endl;
    } else {
      cout << "No solution" << endl;
    }
  }
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("diff_const.in", "r", stdin);
#endif

  solve();

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
