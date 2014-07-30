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

#define N 100002
int adjs[N][3];
int cmap[N];
int ncity = 0;
std::pair<int, int> stamps[N];
//int degree[N];
//bool visited[N];
std::list<int> path;
int add_city(int city, std::map<int, int> &cities) {
  std::map<int, int>::const_iterator it = cities.find(city);
  if (it == cities.end()) {
    cities.insert(std::pair<int, int>(city, ncity));
    cmap[ncity] = city;
    ncity += 1;
    return ncity - 1;
  } else {
    return it->second;
  }
}

void dfs_visit(int u, int pre) {
  for (int i = 1; i <= adjs[u][0]; i++) {
    int v = adjs[u][i];
    if (v != pre) {
      dfs_visit(v, u);
    }
  }
  path.push_front(u);
}
void dfs() {
  for (int i = 0; i < ncity; i++) {
    if (adjs[i][0] == 1) {
      dfs_visit(i, -1);
      break;
    }
  }
}
void solve() {
  int n;
  scanf("%d", &n);
  std::map<int, int> cities;
  for (int i = 0; i < n; i++) {
    scanf("%d %d", &stamps[i].first, &stamps[i].second);
    add_city(stamps[i].first, cities);
    add_city(stamps[i].second, cities);
  }
  for (int i = 0; i < n; i++) {
    int ui = cities.find(stamps[i].first)->second;
    int vi = cities.find(stamps[i].second)->second;
    adjs[ui][adjs[ui][0]+1] = vi;
    adjs[ui][0] += 1;
    adjs[vi][adjs[vi][0]+1] = ui;
    adjs[vi][0] += 1;
  }
  dfs();
  for (std::list<int>::iterator it = path.begin();
       it != path.end(); it++) {
    printf("%d ", cmap[*it]);
  }
  printf("\n");
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  solve();

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
