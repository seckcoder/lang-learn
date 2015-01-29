/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

bool cmpIntv(const Interval &intv1,
    const Interval &intv2) {
  return intv1.start < intv2.start;
}


void mergeInterval(Interval &intv1,
    const Interval &intv2) {
  intv1.start = std::min(intv1.start, intv2.start);
  intv1.end = std::max(intv1.end, intv2.end);
}

bool intersect(const Interval &intv1,
    const Interval &intv2) {
  return !(intv1.start > intv2.end ||
      intv1.end < intv2.start);
}
class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
      if (intervals.empty()) return intervals;
      std::sort(intervals.begin(), intervals.end(),
          cmpIntv);
      vector<Interval> ans;
      Interval acc = intervals[0];
      for (int i = 1; i < intervals.size(); i++) {
        if (intersect(acc, intervals[i])) {
          mergeInterval(acc, intervals[i]);
        } else {
          ans.push_back(acc);
          acc = intervals[i];
        }
      }
      ans.push_back(acc);
      return ans;
      // todo push last
    }
};
