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

#define N 15
#define MAX_S_LEN 80
char seq[N+1][MAX_S_LEN+1];

char *intToString(int v, char *s) {
  char *from = s;
  int cnt = 0;
  while (v != 0) {
    *s = v % 10 + '0';
    v = v / 10;
    cnt += 1;
    s++;
  }
  char *to = s-1;
  while (to > from) {
    std::swap(*from, *to);
    from++;
    to--;
  }
  return s;
}
void apply(int i) {
  uint8 count[10] = {0};
  char *s = seq[i-1];
  while (*s) {
    count[*s - '0'] += 1;
    s++;
  }
  char *target = seq[i];
  for (int i = 0; i < 10; i++) {
    //cout << i << " " << count[i] << endl;
    if (count[i] != 0) {
      target = intToString(count[i], target);
      *target = i + '0';
      target++;
    }
  }
  *target = '\0';
}
void solve() {
  while (scanf("%s", seq[0]) != EOF && seq[0][0] != '-') {
    apply(1);
    //cout << seq[1] << endl;
    if (strcmp(seq[1], seq[0]) == 0) {
      printf("%s is self-inventorying\n", seq[0]);
    } else {
      bool finished = false;
      for (int i = 2; i <= N && !finished; i++) {
        apply(i);
        //cout << seq[i] << endl;
        if (strcmp(seq[i], seq[i-1]) == 0) {
          printf("%s is self-inventorying after %d steps\n", seq[0], i-1);
          finished = true;
        } else {
          for (int j = i-2; j >= 0; j--) {
            if (strcmp(seq[i], seq[j]) == 0) {
              printf("%s enters an inventory loop of length %d\n", seq[0], i-j);
              finished = true;
              break;
            }
          }
        }
      }
      if (!finished) {
        printf("%s can not be classified after 15 iterations\n", seq[0]);
      }
    }
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
