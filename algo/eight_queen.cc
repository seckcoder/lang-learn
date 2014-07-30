#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Pair {
 public:
  int r, c;
  Pair(int hr, int hc) {
    r = hr;
    c = hc;
  }
  bool collide(const Pair &p2) const {
    if (r == p2.r || c == p2.c || abs(r - p2.r) == abs(c - p2.c)) {
      return true;
    }
    return false;
  }
};


void print_path(const vector<Pair> &path) {
  cout << endl;
  for(int i = 0; i < path.size(); i++) {
    cout << path[i].r << " " << path[i].c << endl;
  }
  cout << endl;
}


bool canPlace(const vector<Pair> &path, int r, int c) {
  for(int i = 0; i < path.size(); i++) {
    if (path[i].collide(Pair(r, c))) {
      return false;
    }
  }
  return true;
}

void eight_queen(int col, vector<Pair> &path) {
  if (col > 8) {
    print_path(path);
  } else {
    for(int i = 1; i <= 8; i++) {
      if (canPlace(path, i, col)) {
        path.push_back(Pair(i, col));
        eight_queen(col+1, path);
        path.pop_back();
      }
    }
  }
}


void solve_eight_queen() {
  vector<Pair> path;
  eight_queen(1, path);
}


int main(int argc, const char *argv[])
{
  solve_eight_queen();
  return 0;
}
