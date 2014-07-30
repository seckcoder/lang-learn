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


class Point {
 public:
  uint8 x;
  uint8 y;
};
#define L 100
#define W 100

class Rect {
 public:
  Point ll, ur;
  Rect() {
    ll.x = L;
    ll.y = W;
    ur.x = 0;
    ur.y = 0;
  }
  void update(uint8 x, uint8 y) {
    ll.x = std::min(ll.x, x);
    ll.y = std::min(ll.y, y);
    ur.x = std::max(ur.x, x);
    ur.y = std::max(ur.y, y);
  }
};

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  uint8 l, w;
  char c;
  cin >> l >> w >> c;
  string room[W];
  for (int i = l-1; i >= 0; i--) {
    cin >> room[i];
  }
  Rect president;
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < w; j++) {
      //cout << room[i][j] << endl;
      if (room[i][j] == c) {
        president.update(j,i);
      }
    }
  }

  /*cout << president.ll.x << " " << president.ur.x << endl
      << president.ll.y << " " << president.ur.y << endl;*/

  if (president.ll.x > president.ur.x
      || president.ll.y > president.ur.y) {
    printf("0");
  } else {
    bool deputies[26] = {false};
    // up
    if (president.ur.y < l-1) {
      int y = president.ur.y + 1;
      for (int x = president.ll.x; x <= president.ur.x; x++) {
        if (room[y][x] != '.') {
          deputies[room[y][x]-'A'] = true;
        }
      }
    }
    // left
    if (president.ll.x > 0) {
      int x = president.ll.x - 1;
      for (int y = president.ll.y; y <= president.ur.y; y++) {
        if (room[y][x] != '.') {
          deputies[room[y][x]-'A'] = true;
        }
      }
    }
    // right
    if (president.ur.x < w-1) {
      int x = president.ur.x + 1;
      for (int y = president.ll.y; y <= president.ur.y; y++) {
        if (room[y][x] != '.') {
          deputies[room[y][x]-'A'] = true;
        }
      }
    }
    // down
    if (president.ll.y > 0) {
      int y = president.ll.y - 1;
      for (int x = president.ll.x; x <= president.ur.x; x++) {
        if (room[y][x] != '.') {
          deputies[room[y][x]-'A'] = true;
        }
      }
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) {
      if (deputies[i]) {
        //cout << char(i + 'A') << endl;
        ans += 1;
      }
    }
    cout << ans << endl;
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
