#include <vector>
#include <queue>
using namespace std;

class Point {
  public:
    int x,y;
    Point() {}
    Point(int hx, int hy):x(hx),y(hy) {}
};

void getFourDirectionPoints(int x, int y, int board_size, vector<Point> &points) {
  if (x > 0) points.push_back(Point(x-1,y));
  if (x+1<board_size) points.push_back(Point(x+1,y));
  if (y > 0) points.push_back(Point(x,y-1));
  if (y+1<board_size) points.push_back(Point(x,y+1));
}
bool isCaptured(const vector<vector<char> > &board, int x, int y) {
  int board_size = board.size();
  vector<Point> points;
  getFourDirectionPoints(x,y,board_size, points);
  for (int i = 0; i < points.size(); i++) {
    int next_x = points[i].x,
        next_y = points[i].y;
    if (board[next_x][next_y] == '_') {
      return false;
    }
  }
  return true;
}
void markNotCapturedBFS(vector<vector<char> > &board, int x, int y) {
  queue<Point> que;
  que.push(Point(x,y));
  vector<Point> points;
  int board_size = board.size();
  while (!que.empty()) {
    Point curp = que.front();
    que.pop();
    points.clear();
    getFourDirectionPoints(curp.x,curp.y,board_size,points);
    for (int i = 0; i < points.size(); i++) {
      int next_x = points[i].x,
          next_y = points[i].y;
      if (board[next_x][next_y] == 'O') {
        board[next_x][next_y] = '#';
        que.push(points[i]);
      }
    }
  }
}
void markCaptured(vector<vector<char> > &board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == 'O' && !isCaptured(board, i, j)) {
        board[i][j] = '#'; // mark not captured points
        markNotCapturedBFS(board, i, j);
      }
    }
  }

  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      if (board[i][j] == 'O') {
        board[i][j] = 'M'; // mark as captured
      } else if (board[i][j] == '#') {
        board[i][j] = 'O';
      }
    }
  }
}



int main() {
  return 0;
}
