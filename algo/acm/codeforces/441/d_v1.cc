#define SECK_DEBUG

#undef NDEBUG
#ifdef SECK_DEBUG
#define _GLIBCXX_DEBUG
#endif


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


#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}


#define N 3001
bool visited[N];
int a[N];
int n,m;
int dfs(int v) {
  int size = 0;
  do {
    visited[v] = true;
    v = a[v];
    size += 1;
  } while (!visited[v]);
  return size;
}

int dfs(int v, int b[]) {
  int size = 0;
  b[size] = v;
  do {
    visited[v] = true;
    v = a[v];
    size += 1;
    b[size] = v;
  } while (!visited[v]);
  return size;
}


void firstNonEmptyCircle(int &s, int &e) {
  memset(visited, false, sizeof(visited));
  int b[N];
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      int size = dfs(i, b);
      if (size >= 2) {
        s = b[0];
        e = *std::min_element(b+1, b+size);
        return ;
      }
    }
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &m);

  int c = 0;
  memset(visited, false, sizeof(visited));

  // dfs
  for (int i = 1; i <= n; i++) {
    if (!visited[i]) {
      c += 1;
      dfs(i);
    }
  }
  
  //cout << n-m << " " << c << endl;

  if (n-m == c) {
    printf("0\n");
    return 0;
  } else if (n-m < c) {
    printf("%d\n", c-(n-m));
    // merge circles
    memset(visited, false, sizeof(visited));
    dfs(1);
    int k = n-m;
    for (int i = 2; i <= n && k<c; i++) {
      if (!visited[i]) {
        printf("%d %d ", 1, i);
        k += 1;
        dfs(i);
      }
    }
  } else {
    printf("%d\n", (n-m)-c);
    // divide circles
    
    while (c < n-m) {
      int s, e;
      firstNonEmptyCircle(s, e);
      printf("%d %d ", s, e);
      std::swap(a[s], a[e]);
      c += 1;
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
