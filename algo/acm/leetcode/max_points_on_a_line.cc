// http://oj.leetcode.com/problems/max-points-on-a-line/

#include <vector>
#include <iostream>
#include <map>
#include <cmath>
#include <limits>

using std::vector;
using namespace std;

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
  /*bool operator==(const Point &p) {
    return (x == p.x) && (y == p.y);
  }*/
};

bool operator==(const Point &p1, const Point &p2) {
  return (p1.x == p2.x) && (p1.y == p2.y);
}

bool align(const Point &p1, const Point &p2, const Point &p3) {
  // (x1 - x2) / (x2 - x3) == (y1 - y2) / (y2 - y3)
  return ((p1.x - p2.x) * (p2.y - p3.y)) == ((p2.x - p3.x) * (p1.y - p2.y));
}


#define sloap_map std::map<float, int>
#define precision 10000

float round_by_prec(float v) {
  return floor(v * precision) / precision;
}

float calc_sloap(const Point &p1, const Point &p2) {
  if (p1.x == p2.x) {
    return std::numeric_limits<float>::max();
  } else {
    return round_by_prec((float)(p1.y - p2.y) / (float)(p1.x - p2.x));
  }
}

class Solution {
public:
    int maxPoints(vector<Point> &points) {
      int max_num = 0;
      for(int i = 0 ; i < points.size(); i++) {
        sloap_map a_sloap_map;
        int tmp_max_num = 0;
        int same_points_num = 1;
        for(int j = i+1; j < points.size(); j++) {
          if (points[i] == points[j]) {
            same_points_num += 1;
          } else {
            float cur_sloap = calc_sloap(points[i], points[j]);
            sloap_map::iterator it = a_sloap_map.find(cur_sloap);
            if (it == a_sloap_map.end()) {
              a_sloap_map.insert(std::pair<float,int>(cur_sloap, 1));
              it = a_sloap_map.find(cur_sloap);
            } else {
              it->second += 1;
            }
            if (it->second >= tmp_max_num) {
              tmp_max_num = it->second;
            }
          }
        }
        tmp_max_num += same_points_num;
        if (tmp_max_num >= max_num) {
          max_num = tmp_max_num;
        }
      }
      return max_num;
    }
};


int main(int argc, const char *argv[]) {
  Solution sol;
  vector<Point> points;
  points.push_back(Point(0,0));
  /*points.push_back(Point(0,0));
  points.push_back(Point(1,1));*/
  /*points.push_back(Point(0,2));
  points.push_back(Point(1,0));
  points.push_back(Point(1,1));*/
  cout << sol.maxPoints(points) << endl;
}
