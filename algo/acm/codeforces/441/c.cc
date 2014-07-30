//#define SECK_DEBUG

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

int n,m,k;
enum Direction {DIR_RIGHT, DIR_LEFT};
class Point {
 public:
  int x, y;
  Point(int hx, int hy):x(hx), y(hy) {}
  Direction step(Direction dir) {
    if (dir == DIR_RIGHT) {
      if (y == m) {
        x += 1;
        return DIR_LEFT;
      } else {
        y += 1;
        return DIR_RIGHT;
      }
    } else  {
      if (y == 1) {
        x += 1;
        return DIR_RIGHT;
      } else {
        y -= 1;
        return DIR_LEFT;
      }
    }
  }
  bool operator==(const Point &p1) {
    return (x == x) && (y == y);
  }
  bool operator!=(const Point &p1) {
    return !((*this) == p1);
  }
};


int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d %d %d", &n, &m, &k);
  vector<vector<Point> > tubes(k);
  Point p(1, 1);
  Direction dir = DIR_RIGHT;
  for (int i = 0; i < k-1; i++) {
    tubes[i].push_back(p);
    dir = p.step(dir);
    tubes[i].push_back(p);
    dir = p.step(dir);
  }
  while (p.x <= n && p.y <= m) {
    tubes[k-1].push_back(p);
    dir = p.step(dir);
  }

  for (int i = 0; i < tubes.size(); i++) {
    cout << tubes[i].size();
    for (int j = 0; j < tubes[i].size(); j++) {
      printf(" %d %d", tubes[i][j].x, tubes[i][j].y);
    }
    printf("\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
