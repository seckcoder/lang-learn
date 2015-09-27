



/* Suppose we want to use Point as the key.
 *
 *
 * */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::ostream;
struct Point {
  int x,y;
  Point(int hx, int hy)
    :x(hx), y(hy) {}
};

ostream &operator<<(ostream &os, const Point &p) {
  os << "(" << p.x << "," << p.y << ")";
  return os;
}

namespace std {
  template <>
    struct hash<Point> {
      std::size_t operator()(const Point &p) const {
        return hash<std::string>()(std::to_string(p.x) + "," + std::to_string(p.y));
      }
    };
};


namespace std {
  template <>
    struct equal_to<Point> {
      bool operator()(const Point &p1, const Point &p2) const {
        return p1.x == p2.x && p1.y == p2.y;
      }
    };
};


int main() {
  unordered_map<Point, vector<Point>> point_map;
  point_map[Point(1,1)].push_back(Point(1,2));
  point_map[Point(1,1)].push_back(Point(2,3));
  point_map[Point(2,1)].push_back(Point(1,2));

  for (auto pair: point_map) {
    cout << pair.first << ": ";
    for (auto p:pair.second) {
      cout << p << ",  ";
    }
    cout << endl;
  }
  return 0;
}
