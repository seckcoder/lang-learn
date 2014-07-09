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

#define N 100001

bool visited[N];
int a[N];
vector<int> cur;
vector<int> pre;
vector<std::pair<int, int> > edges;
#define add_edge(u, v) edges.push_back(std::pair<int,int>((u), (v)))
int dfs(int u) {
  while (!visited[a[u]]) {
    cur.push_back(a[u]);
    visited[a[u]] = true;
    u = a[u];
  }
  if (!pre.empty()) {
    add_edge(pre.back(), cur.front());
  }
  pre.insert(pre.end(), cur.begin(), cur.end());
  cur.clear();
  return a[u];
}
int degree[N+1];
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    //cin >> a[i];
    degree[a[i]] += 1;
  }
  dfs(1);
  if (pre.size() == n) {
    printf("0\n");
  } else {
    memset(visited, false, sizeof(visited));
    cur.clear();
    pre.clear();
    int last = 0;
    for (int i = 1; i <= n; i++) {
      if (degree[i] == 0) {
        cur.push_back(i);
        visited[i] = true;
        last = dfs(i);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!visited[i]) {
        cur.push_back(i);
        visited[i] = true;
        last = dfs(i);
      }
    }
    if (last != pre.front()) {
      add_edge(last, pre.front());
    }
    cout << edges.size() << endl;
    for (int i = 0; i < edges.size(); i++) {
      printf("%d %d\n", edges[i].first, edges[i].second);
      //cout << edges[i].first << " " << edges[i].second << endl;
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
