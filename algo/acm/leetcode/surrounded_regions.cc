#include <vector>
#include <queue>
#include <iostream>
using namespace std;


class MPoint {
  public:
    int x,y;
    MPoint(int hx, int hy):x(hx),y(hy){}
};

class Solution {
public:
    void solve(vector<vector<char>> &board) {
        int m = board.size();
        if (m == 0) return;
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                floodfillBFS(board, i, 0);
            }
            if (board[i][n-1] == 'O') {
                floodfillBFS(board, i, n-1);
            }
        }
        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') {
                floodfillBFS(board, 0, i);
            }
            if (board[m-1][i] == 'O') {
                floodfillBFS(board, m-1, i);
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '#') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
    void getFourDirectionMPoints(int x, int y, int m, int n, vector<MPoint> &points) {
        if (x+1 < m)
            points.push_back(MPoint(x+1,y));
        if (y+1 < n)
            points.push_back(MPoint(x,y+1));
        if (x > 0)
            points.push_back(MPoint(x-1,y));
        if (y > 0)
            points.push_back(MPoint(x,y-1));
    }
    void floodfillDFS(vector<vector<char>> &board, int x, int y) {
        board[x][y] = '#';
        int m = board.size(),
            n = board[0].size();
        vector<MPoint> points;
        getFourDirectionMPoints(x,y,m,n, points);
        for (int i = 0; i < points.size(); i++) {
            int next_x = points[i].x,
                next_y = points[i].y;
            if (board[next_x][next_y] == 'O') {
                floodfillDFS(board, next_x, next_y);
            }
        }
    }

    void floodfillBFS(vector<vector<char> > &board, int x, int y) {
      queue<MPoint> queue;
      queue.push(MPoint(x,y));
      board[x][y] = '#';
      int m = board.size(),
          n = board.size();
      vector<MPoint> points;
      while (!queue.empty()) {
        MPoint curp = queue.front();
        queue.pop();
        points.clear();
        getFourDirectionMPoints(curp.x,curp.y,m,n,points);
        for (int i = 0; i < points.size(); i++) {
          int next_x = points[i].x,
              next_y = points[i].y;
          if (board[next_x][next_y] == 'O') {
            board[next_x][next_y] = '#';
            queue.push(points[i]);
          }
        }
      }
    }
};


int main() {
  Solution sol;
  vector<char> bd1 = {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'} ;
  vector<vector<char> > board;
  board.push_back(bd1);
  sol.solve(board);
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << board[i][j];
    }
    cout << endl;
  }
  return 0;
}
