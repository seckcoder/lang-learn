

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/*
 *
 *
 * Find the rectangle with largest area in a circular array.
 *
 *
 *
 *
 *
 */ 

void setCoords(vector<int> &coords, int c1,int c2, int r1, int r2) {
  coords[0] = r1;
  coords[1] = c1;
  coords[2] = r2;
  coords[3] = c2;
}

class Result {
  public:
    int max_sum;
    vector<int> coords;
    Result(int max_sum_, vector<int> coords_)
      :max_sum(max_sum_), coords(coords_) {}
    friend ostream &operator<<(ostream &os, const Result &res) ;
};

ostream &operator<<(ostream &os, const Result &res) {
  os << "Sum: " << res.max_sum << endl;
  os << "TopLeftIndex: " << res.coords[0]<< ", " << res.coords[1] << endl;
  os << "BottomRightIndex: " << res.coords[2]<< ", " << res.coords[3] << endl;
  return os;
}

Result maxSubArray(vector<vector<int>> &mat) {

  int nRows = mat.size();
  if (nRows == 0) return Result(0, {});
  int nCols = mat[0].size();
  if (nCols == 0) return Result(0, {});

  vector<vector<int>> rowSum(nRows, vector<int>(2*nCols, 0));

  for (int i = 0; i < nRows; i++) {
    rowSum[i][0] = mat[i][0];
    for (int j = 1; j < 2*nCols; j++) {
      rowSum[i][j] = rowSum[i][j-1] + mat[i][j%nCols];
    }
  }

  int max_sub;
  bool initialized = false;
  vector<int> coords(4);
  for (int j1 = 0; j1 < nCols; j1++) {
    for (int j2 = j1; j2 < j1+nCols; j2++) {
      int max_sub_row;
      int r1, r2;
      for (int i = 0; i < nRows; i++) {
        int row_sum;
        if (j1 == j2) row_sum = rowSum[i][j2%nCols];
        else row_sum = rowSum[i][j2%nCols] - rowSum[i][j1-1];

        if (i == 0 || max_sub_row < 0) max_sub_row = row_sum, r1 = i, r2 = i;
        else {
          max_sub_row += row_sum;
          r2 = i;
        }
      }
      if (!initialized) max_sub = max_sub_row, initialized = true, setCoords(coords, j1, j2, r1, r2);
      else if (max_sub_row > max_sub) {
        max_sub = max_sub_row;
        setCoords(coords, j1, j2, r1, r2);
      }
    }
  }

  
  return Result(max_sub, coords);
}

int main() {
  std::ifstream ifs("a.txt", std::ifstream::in);
  int nCols, nRows;
  ifs >> nRows >> nCols;
  
  vector<vector<int>> mat(nRows, vector<int>(nCols));
  for (int i = 0; i < nRows; i++) {
    for (int j = 0; j < nCols; j++) {
      ifs >> mat[i][j];
    }
  }
  cout << maxSubArray(mat) << endl;
  return 0;
}
