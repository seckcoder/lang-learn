//#define SECK_DEBUG

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

#define N 200

// get ord of x
int getT(int f[], int n, int x) {
  int fx = x;
  int t = 0;
  do {
    t += 1;
    fx = f[fx];
  } while (fx != x);
  return t;
}

// apply for k times
int apply(int f[], int T[], int n, int x, int k) {
  k = k % T[x];
  for (int i = 1; i <= k; i++) {
    x = f[x];
  }
  return x;
}

void solve() {
  int n;
  int f[N+1];
  int T[N+1];
  char str[N+1];
  char tmp[N+1];
  scanf("%d", &n);
  while (n != 0) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", &f[i]);
    }
    for (int i = 1; i <= n; i++) {
      T[i] = getT(f, n, i);
    }
    int k;
    scanf("%d", &k);
    while (k != 0) {
      getchar();
      gets(str);
      int len = strlen(str);
      for (int i = len; i < n; i++) {
        str[i] = ' ';
      }
      str[n] = '\0';
      for (int i = 1; i <= n; i++) {
        //cout << i << " " << str[i] << " " << apply(f, T, n, i, k) << endl;
        tmp[apply(f, T, n, i, k)-1] = str[i-1];
      }
      tmp[n] = '\0';
      printf("%s\n", tmp);
      scanf("%d", &k);
    }
    printf("\n");
    scanf("%d", &n);
  }
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
