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

#define N 200

typedef std::pair<int, int> Edge;
bool vv[N+1][N+1];
Edge es[N+1];
int n;
int degree[N+1];

void addEdge(const Edge &e) {
  vv[e.first][e.second] = true;
  vv[e.second][e.first] = true;
  degree[e.first] += 1;
  degree[e.second] += 1;
}

void removeEdge(const Edge &e) {
  vv[e.first][e.second] = false;
  vv[e.second][e.first] = false;
  degree[e.first] -= 1;
  degree[e.second] -= 1;
}


bool visited[N+1];
int dfs(int u) {
  visited[u] = true;
  int max_h = 0;
  for (int v = 1; v <= n; v++) {
    if (vv[u][v] && !visited[v]) {
      max_h = std::max(dfs(v)+1, max_h);
    }
  }
  return max_h;
}
void connectedComponents(int start, std::vector<int> &cc) {
  memset(visited, false, sizeof(visited));
  dfs(start);
  for (int i = 1; i <= n; i++) {
    if (visited[i]) {
      cc.push_back(i);
    }
  }
}

int longestPath(const vector<int> &cc) {
  int max_h = 0;
  for (int i = 0; i < cc.size(); i++) {
    if (degree[cc[i]] == 1) {
      // is leaf
      memset(visited, true, sizeof(visited));
      for (int j = 0; j < cc.size(); j++) {
        visited[cc[j]] = false;
      }
      max_h = std::max(dfs(cc[i]), max_h);
    }
  }
  return max_h;
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  //cin >> n;
  for (int i = 0; i < n-1; i++) {
    scanf("%d %d", &es[i].first, &es[i].second);
    //cin >> es[i].first >> es[i].second;
    addEdge(es[i]);
  }

  int ans = 0;
  for (int i = 0; i < n-1; i++) {
    removeEdge(es[i]);
    vector<int> cc1, cc2;
    connectedComponents(es[i].first, cc1);
    connectedComponents(es[i].second, cc2);
    if (cc1.size() < cc2.size()) {
      int lp1 = longestPath(cc1);
      if (lp1 != 0) {
        int lp2 = longestPath(cc2);
        ans = std::max(lp1 * lp2 , ans);
      }
    } else {
      int lp2 = longestPath(cc2);
      if (lp2 != 0) {
        int lp1 = longestPath(cc1);
        ans = std::max(lp1 * lp2 , ans);
      }
    }
    addEdge(es[i]);
  }
  printf("%d\n", ans);
  //cout << ans << endl;

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
