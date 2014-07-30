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

void solve() {
  int t;
  scanf("%d", &t);
  while (t>=1) {
    t -= 1;
    int n;
    scanf("%d", &n);
    std::stack<int> s;
    int prev_num = 0;
    for (int i = 0; i < n; i++) {
      int lp_num;
      scanf("%d", &lp_num);
      for (int j = 0; j < lp_num-prev_num; j++) {
        s.push(0);
      }
      int cur = s.top() + 1;
      printf("%d ", cur);
      s.pop();
      if (!s.empty()) s.top() += cur;
      prev_num = lp_num;
    }
    printf("\n");
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
