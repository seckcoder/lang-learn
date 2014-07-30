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

class Rect {
 public:
  int w,h;
  int id;
  friend istream &operator>>(istream &is, Rect &r) {
    is >> r.w >> r.h;
    return is;
  }
  int64 area() const {
    int64 w2 = w;
    w2 *= w;
    int64 h2 = h;
    h2 *= h;
    return w2 + h2;
  }
  bool operator<(const Rect &r) {
    return w < r.w && h < r.h;
  }
};

bool cmpRect(const Rect &r1, const Rect &r2) {
  return r1.area() < r2.area();
}

#define N 5000

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif


  int n;
  Rect card;
  cin >> n >> card;
  Rect env[N];
  int fn = 0;
  for (int i = 0; i < n; i++) {
    Rect tmp;
    cin >> tmp;
    if (card < tmp) {
      env[fn] = tmp;
      env[fn].id = i+1;
      fn += 1;
    }
  }
  if (fn == 0) {
    printf("0\n");
  } else {
    std::sort(env, env+fn, cmpRect);

    int dp[N];
    int prev[N];
    int max_chain_idx = 0;
    for (int i = 0; i < fn; i++) {
      // init
      dp[i] = 1;
      prev[i] = -1;
      // update
      for (int j = i-1; j >= 0; j--) {
        if (env[j] < env[i] && dp[j] + 1 > dp[i]) {
          dp[i] = dp[j] + 1;
          prev[i] = j;
        }
      }
      if (dp[i] > dp[max_chain_idx]) {
        max_chain_idx = i;
      }
    }
    vector<int> env_idx_vec(dp[max_chain_idx]);
    int cnt = dp[max_chain_idx]-1;
    for (int i = max_chain_idx;
         i >= 0; i = prev[i]) {
      env_idx_vec[cnt] = i;
      cnt -= 1;
    }
    printf("%d\n", dp[max_chain_idx]);
    for (int i = 0; i < dp[max_chain_idx]; i++) {
      cout << env[env_idx_vec[i]].id << " ";
    }
    cout << endl;
  }


#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
