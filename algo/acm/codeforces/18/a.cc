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

enum Dir {up, right, down, left};
enum TriangleType {RIGHT, ALMOST, NEITHER};
class Point {
 public:
  int x,y;
  Point move(Dir d) const {
    Point p;
    switch (d) {
      case up:
        p.x = x;
        p.y = y+1;
        break;
      case right:
        p.x = x+1;
        p.y = y;
        break;
      case down:
        p.x = x;
        p.y = y-1;
        break;
      case left:
        p.x = x-1;
        p.y = y;
        break;
    }
    return p;
  }
  friend std::istream& operator>>(std::istream &is, Point &p) {
    is >> p.x >> p.y;
    return is;
  }
};

#define square(v) ((v)*(v))
int dis2(const Point &p1, const Point &p2) {
  return square(p1.x - p2.x) + square(p1.y - p2.y);
}
class Triangle {
 public:
  Point p1, p2, p3;
  Triangle(const Point &hp1, const Point &hp2, const Point &hp3):p1(hp1),p2(hp2),p3(hp3) {
  }
  static bool isRight(const Point &p1, const Point &p2, const Point &p3) {
    int a2 = dis2(p1, p2);
    int b2 = dis2(p2, p3);
    int c2 = dis2(p3, p1);
    double a = std::sqrt(a2);
    double b = std::sqrt(b2);
    double c = std::sqrt(c2);
    if (!(a+b > c && b+c > a && a+c > b)) return false;
    //cout << a2 << " " << b2 << " " << c2 << endl;
    return (a2 + b2 == c2 ||
            b2 + c2 == a2 ||
            a2 + c2 == b2) ;
  }
  TriangleType getType() const {
    if (isRight(p1, p2, p3)) return RIGHT;
    for (int i = int(up); i <= int(left); i++) {
      Point hp1 = p1.move(Dir(i));
      if (isRight(hp1, p2, p3)) return ALMOST;
    }
    for (int i = int(up); i <= int(left); i++) {
      Point hp2 = p2.move(Dir(i));
      if (isRight(p1, hp2, p3)) return ALMOST;
    }
    for (int i = int(up); i <= int(left); i++) {
      Point hp3 = p3.move(Dir(i));
      if (isRight(p1, p2, hp3)) return ALMOST;
    }
    return NEITHER;
  }
};

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  Point p1, p2, p3;
  cin >> p1 >> p2 >> p3;
  switch (Triangle(p1, p2, p3).getType()) {
    case RIGHT:
      printf("RIGHT\n");
      break;
    case ALMOST:
      printf("ALMOST\n");
      break;
    case NEITHER:
      printf("NEITHER\n");
      break;
  }
#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
