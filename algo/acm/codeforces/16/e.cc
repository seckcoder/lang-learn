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

#define N 18
#define M 1<<N
#define alive(s, i) (((s)>>(i)) & 1)
#define C2(k) (((k)*((k)-1))>>1)
int n;
double a[N][N];
double d[M] = {0};
bool visited[M];

int alive_num(int s) {
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (alive(s,i)) {
      cnt += 1;
    }
  }
  return cnt;
}


void solve() {
  int m = (1<<n);
  std::queue<int> q;
  q.push(m-1);
  visited[m-1] = true;
  std::set<int> finals;
  for (int i = 0; i < n; i++) {
    finals.insert((1<<i));
  }
  int cnt = 0;
  while (!q.empty()) {
    cnt += 1;
    int src = q.front();
    q.pop();
    int memnum = alive_num(src);
    //cout << memnum << endl;
    //cout << src << endl;
    double pbase = C2(memnum);
    for (int i = 0; i < n; i++) {
      if (alive(src, i)) {
        for (int j = i+1; j < n; j++) {
          if (alive(src, j)) {
            int destj = src  ^ (1<<i);
            d[destj] += (d[src] * a[j][i])/pbase;
            int desti = src ^ (1<<j);
            d[desti] += (d[src] * a[i][j])/pbase;
            if (finals.find(desti) == finals.end()) {
              if (!visited[desti]) {
                q.push(desti);
                visited[desti] = true;
              }
              if (!visited[destj]) {
                q.push(destj);
                visited[destj] = true;
              }
            }
          }
        }
      }
    }
  }
  //cout << cnt << " " << m << endl;
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
    }
  }

  int m = (1<<n);
  d[m-1] = 1;
  solve();
 
  for (int i = 0; i < n; i++) {
    printf("%.6f ", d[1<<i]);
    //cout << d[1<<i] << " ";
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
