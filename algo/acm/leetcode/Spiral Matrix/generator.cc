


class SpiralCoordOp {
  public:
    SpiralCoordOp() {}
    void operator()(int x, int y) {
    }
};



template <class T>
void spiralFrameTraverse(int px, int py, int rx, int ry,
    T op) {
  int x,y;
  if (px == rx) {
    x = px;
    for (y = py; y <= ry; y++) {
      op(x,y);
    }
  } else if (py == ry) {
    y = py;
    for (x = px; x <= rx; x++) {
      op(x,y);
    }
  } else {

    // Right: Fix x

    x = px;
    for (y = py; y < ry; y++) {
      op(x,y);
    }


    // Down: Fix y

    y = ry;
    
    for (x = px; x < rx; x++) {
      op(x,y);
    }

    // Left: Fix x

    x = rx;
    for (y = ry; y > py; y--) {
      op(x,y);
    }

    // Up: Fix y

    for (x = rx; x > px; x--) {
      op(x, y);
    }
  }
}

/* m x n matrix */
template <class T>
void spiralTraverse(int m, int n, T op) {
  int px = 0,
      py = 0,
      rx = m-1,
      ry = n-1;

  while ((px <= rx) && (py <= ry)) {
    spiralFrameTraverse(px, py, rx, ry, op);
    px += 1;
    py += 1;
    rx -= 1;
    ry -= 1;
  }
}


#include <vector>
using namespace std;
class MySpiralCoordOp: public SpiralCoordOp {
  public:
    vector<int> *pvec;
    vector<vector<int>> *pmatrix;
    MySpiralCoordOp(vector<int> &vec, vector<vector<int>> &matrix) {
      pvec = &vec;
      pmatrix = &matrix;
    }
    void operator()(int x, int y) {
      pvec->push_back((*pmatrix)[x][y]);
    }
};

class Solution {
  public:
  vector<int> spiralOrder(vector<vector<int> > &matrix) {
    vector<int> trav;
    int m = matrix.size();
    if (m == 0) return trav;
    int n = matrix[0].size();
    if (n == 0) return trav;
    MySpiralCoordOp op(trav, matrix);
    spiralTraverse(m, n, op);
    return trav;
  }
};
