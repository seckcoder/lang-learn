#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

class MPoint {
  public:
    int x,y;
    MPoint(int hx, int hy) : x(hx), y(hy) {}
    bool conflict(const MPoint &p) const {
      return x == p.x || y == p.y || std::abs(p.y - y) == std::abs(p.x-x);
    }
};

bool conflict(const vector<MPoint> &pos, int x, int y) {
  for (int i = 0; i < pos.size(); i++) {
    if (pos[i].conflict(MPoint(x,y))) return true;
  }
  return false;
}
class Solution {
  public:
    int totalNQueens(int n) {
      vector<MPoint> pos;
      return recur(0,n, pos);
    }
    int recur(int i, int n, vector<MPoint> &pos) {
      if (i >= n) {
        return 1;
      } else {
        int sol = 0;
        for (int j = 0; j < n; j++) {
          if (!conflict(pos, i, j)) {
            pos.push_back(MPoint(i,j));
            sol += recur(i+1, n, pos);
            pos.pop_back();
          }
        }
        return sol;
      }
    }
};
