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
#include <algorithm>
#include <iostream>
using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

// append intervals[p,r] to ans. assert [p,r] in range of intervals
void appendIntervals(vector<Interval> &ans, const vector<Interval> &intervals,
    int p, int r) {
  for (int i = p; i <= r; i++) {
    ans.push_back(intervals[i]);
  }
}

// merge two intervals that intersect with each other. Assert intv1 intersect with intv2
void mergeIntersectInterval(Interval &intv1, const Interval &intv2) {
  intv1.start = std::min(intv1.start, intv2.start);
  intv1.end = std::max(intv1.end, intv2.end);
}

int findIntersectIntervalsInRange(const vector<Interval> &intervals, int cur, int end_x) {
  int i;
  for (i = cur; i < intervals.size() && intervals[i].start <= end_x; i++) {}
  return i-1;
}

void mergeRange(Interval &intv1, const vector<Interval> &intervals, int p,
    int r)  {
  for (int i = p; i <= r; i++) {
    mergeIntersectInterval(intv1, intervals[i]);
  }
}

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
      vector<Interval> ans;
      if (intervals.empty()) {
        ans.push_back(newInterval);
        return ans;
      }
      for (int cur = 0; cur < intervals.size();) {
        if (newInterval.end < intervals[cur].start) {
          ans.push_back(newInterval);
          appendIntervals(ans, intervals, cur, intervals.size()-1);
          return ans;
        } else if (newInterval.end <= intervals[cur].end) {
          mergeIntersectInterval(newInterval, intervals[cur]);
          ans.push_back(newInterval);
          appendIntervals(ans, intervals, cur+1, intervals.size()-1);
          return ans;
        } else if (newInterval.start <= intervals[cur].end) {
          // end >= cur
          int end = findIntersectIntervalsInRange(intervals, cur+1, newInterval.end);
          mergeRange(newInterval, intervals, cur, end);
          ans.push_back(newInterval);
          appendIntervals(ans, intervals, end+1, intervals.size()-1);
          return ans;
        } else {
          ans.push_back(intervals[cur]);
          cur += 1;
        }
      }
      ans.push_back(newInterval);
      return ans;
    }
};


int main() {
  const int n = 1;
  int intv_vals [n<<1] = {
    1,2
  };
  vector<Interval> intvs;
  for (int i = 0; i < (n<<1); i+=2) {
    intvs.push_back(Interval(intv_vals[i], intv_vals[i+1]));
  }

  Solution sol;
  vector<Interval> ans = sol.insert(intvs, Interval(3,4));
  for (int i = 0; i < ans.size();i++) {
    cout << ans[i].start << " " << ans[i].end << endl;
  }
}
