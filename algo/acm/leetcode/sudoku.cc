#include <vector>

using namespace std;

class Solution {
  public:
    int n;
    void solveSudoku(vector<vector<char> > &board) {
      n = board.size();
      recur(board, 0, 0);
    }
    bool conflict(const vector<vector<char> > &board, int x, int y, int k) {
      for (int i = 0; i < n; i++) {
        if (i != x && board[i][y] == k) {
          return true;
        }
      }
      for (int j = 0; j < n; j++) {
        if (j != y && board[x][j] == k) return true;
      }
      int bi = x /3, bj = y / 3;
      for (int i = bi*3; i < (bi+1)*3; i++) {
        for (int j = bj*3; j < (bj+1)*3; j++) {
          if (i != x && j != y && board[i][j] == k) return true;
        }
      }
      return false;
    }
    bool recur(vector<vector<char> > &board, int x, int y) {
      if (x >= n) return true;
      if (y >= n) {
        return recur(board, x+1, 0);
      }
      if (board[x][y] != '.') return recur(board, x,y+1);
      for (char k = '1'; k <= '9'; k++) {
        if (!conflict(board, x, y, k)) {
          board[x][y] = k;
          if (recur(board, x,y+1)) return true;
          board[x][y] = '.';
        }
      }
      return false;
    }
};

