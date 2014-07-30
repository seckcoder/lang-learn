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

class Point {
 public:
  int x, y;
  Point () {}
  Point (int hx, int hy):x(hx), y(hy) {}
  bool operator==(const Point &p) const {
    return x == p.x && y == p.y;
  }
};

class Segment {
 public:
  Point p1, p2;
  Segment() {}
  Segment(const Point &hp1, const Point &hp2):p1(hp1),p2(hp2) {}
  friend istream &operator>>(istream &is, Segment &s) {
    is >> s.p1.x >> s.p1.y >> s.p2.x >> s.p2.y;
    return is;
  }
  bool perpendicular(const Segment &s) const {
    int64 ax = (p2.x - p1.x);
    int64 ay = (p2.y - p1.y);
    int64 bx = s.p2.x - s.p1.x;
    int64 by = s.p2.y - s.p1.y;
    return ax * bx + ay*by == 0;
  }
};

vector<Segment> segs(4);
bool findSegment(int j, const Point &p, Point &other_p) {
  for (int i = j; i < 4; i++) {
    if (segs[i].p1 == p) {
      other_p = segs[i].p2;
      std::swap(segs[j], segs[i]);
      return true;
    } else if (segs[i].p2 == p) {
      other_p = segs[i].p1;
      std::swap(segs[j], segs[i]);
      return true;
    }
  }
  return false;
}

bool validRectangle(const vector<Point> &pts,
                    const vector<Segment> &segs) {
  for (int i = 0; i < pts.size(); i++) {
    for (int j = i+1; j < pts.size(); j++) {
      if (pts[i] == pts[j]) {
        return false;
      }
    }
  }
  if (!segs[0].perpendicular(segs[1])) return false;
  if (!segs[1].perpendicular(segs[2])) return false;
  if (!segs[2].perpendicular(segs[3])) return false;
  if (!segs[3].perpendicular(segs[0])) return false;
  return true;
}
bool parallelToAxis(const vector<Point> &pts,
                    const vector<Segment> &segs) {
  Segment x(Point(0, 0), Point(1, 0));
  Segment y(Point(0, 0), Point(0, 1));
  for (int i = 0; i < segs.size(); i++) {
    if (!segs[i].perpendicular(x) &&
        !segs[i].perpendicular(y)) {
      return false;
    }
  }
  return true;
}
bool solve() {
  vector<Point> pts;
  Segment *pa = &segs[0];
  pts.push_back(pa->p1);
  pts.push_back(pa->p2);
  Point other_p;
  if (!findSegment(1, pts[1], other_p)) {
    return false;
  }
  pts.push_back(other_p);
  if (!findSegment(2, pts[2], other_p)) {
    return false;
  }
  pts.push_back(other_p);
  if (!validRectangle(pts, segs)) {
    return false;
  }
  if (!parallelToAxis(pts, segs)) {
    return false;
  }
  return true;
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  bool res = true;

  for (int i = 0; i < 4; i++) {
    cin >> segs[i];
  }
  if (solve()) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
