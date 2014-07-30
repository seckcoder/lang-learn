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
typedef char int8;

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

ostream &operator<<(ostream &os, const int8 v) {
  os << (int)v;
  return os;
}
istream &operator>>(istream &is, int8 &v) {
  int tmp;
  is >> tmp;
  v = (int8)tmp;
  return is;
}

#define N 10
uint8 n, a, b;
int8 h[N];

uint8 fballs[N];

// file at the ith for ntimes
// assert 0< i < n-1
inline void fire(uint8 i, uint8 ntimes) {
  h[i] -= ntimes * a;
  h[i-1] -= ntimes * b;
  h[i+1] -= ntimes * b;
}

inline void revFire(uint8 i, uint8 ntimes) {
  h[i] += ntimes * a;
  h[i-1] += ntimes * b;
  h[i+1] += ntimes * b;
}


#define FT(h, base) (((h)<0)?0:((h)/(base) + 1))

inline uint8 min(uint8 a, uint8 b) {
  return (a<b)?a:b;
}
inline uint8 max(uint8 a, uint8 b) {
  return (a>b)?a:b;
}

// 带vector回溯的深搜
uint8 dfs(uint8 i, uint8 e, vector<uint8> &balls) {
  if (i == e) {
    uint8 k = max(FT(h[i-1], b), FT(h[i], a));
    balls[i] = k;
    return k;
  } else {
    uint8 ans = 161;
    uint8 selected_k = 0;
    uint8 fb = FT(h[i-1], b);
    uint8 fa = FT(h[i], a);

    vector<uint8> tmp_balls(n);
    for (uint8 k = fb;
         k <= max(fb, fa);
         k+=1) {
      fire(i, k);
      uint8 tmp = dfs(i+1, e, tmp_balls); 
      if (tmp+k < ans) {
        ans = tmp + k;
        balls[i] = k;
        // update balls
        for (uint8 j = i+1; j <= e; j++) {
          balls[j] = tmp_balls[j];
        }
      }
      revFire(i, k);
    }
    return (ans==161)?0:ans;
  }
}

void dfsSearch(uint8 i, uint8 e) {
  vector<uint8> balls(n);
  dfs(i, e, balls);
  for (int i = 1; i < n-1; i++) {
    fballs[i] += balls[i];
  }
}

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  cin >> n >> a >> b;
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  // 0
  uint8 balls = FT(h[0], b);
  fire(1, balls);
  fballs[1] += balls;

  // n-1
  balls = FT(h[n-1], b);
  fire(n-2, balls);
  fballs[n-2] += balls;

  dfsSearch(1, n-2);
  uint8 ans = 0;
  for (int i = 1; i < n-1; i++) {
    ans += fballs[i];
  }
  cout << ans << endl;
  for (int i = 1; i < n-1; i++) {
    while (fballs[i] != 0) {
      cout << i+1 << " ";
      fballs[i] -= 1;
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
