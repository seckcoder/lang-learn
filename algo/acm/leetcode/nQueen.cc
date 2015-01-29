#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    vector<vector<string> > res;
    int n;
    vector<vector<string> > solveNQueens(int hn) {
        n = hn;
        vector<int> pos;
        res.clear();
        rec(0, pos);
        return res;
    }
    void rec(int i, vector<int> &pos) {
        if (i >= n) {
            pushOne(pos);
        } else {
            for (int j = 0; j < n; j++) {
                if (valid(i, j, pos)) {
                    pos.push_back(j);
                    rec(i+1, pos);
                    pos.pop_back();
                }
            }
        }
    }
    bool valid(int i, int j, const vector<int> &pos) {
        for (int x = 0; x < i; x++) {
            if (pos[x] == j) return false;
            if (align(x,pos[x], i, j)) {
                return false;
            }
        }
        return true;
    }
    bool align(int x1, int y1, int x2, int y2) {
        return (abs(x1-x2) == abs(y1-y2));
    }
    void pushOne(const vector<int> &pos) {
        vector<string> tmp(n);
        for (int i = 0; i < n; i++) {
            tmp[i] = string(n, '.');
        }
        for (int i = 0; i < n; i++) {
            tmp[i][pos[i]] = 'Q';
        }
        res.push_back(tmp);
    }
};

int main() {
  Solution sol;
  vector<vector<string> > res = sol.solveNQueens(8);
  for (int i = 0; i < res.size(); i++) {
    for (int j = 0; j < res[i].size(); j++) {
      cout << res[i][j] << endl;
    }
    cout << endl;
  }
  return 0;
}
