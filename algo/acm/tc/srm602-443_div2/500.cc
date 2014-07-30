#include <vector>

using namespace std;

class CirclesCountry {
 public:
  int leastBorders(vector <int> X, vector <int> Y, vector <int> R, int x1, int y1, int x2, int y2) {
    int n = X.size();
    sortCircles(X, Y, R, 0, n-1);
    int p1_cross = 0;
    int p2_cross = 0;
    for(int i = 0; i < n; i++) {
      bool contain_p1 = contain(X[i], Y[i], R[i], x1, y1);
      bool contain_p2 = contain(X[i], Y[i], R[i], x2, y2);
      if (contain_p1 && contain_p2) {
        break;
      } else if (contain_p1) {
        p1_cross += 1;
      } else if (contain_p2) {
        p2_cross += 1;
      }
    }
    return p1_cross + p2_cross;
  }
  void sortCircles(vector<int> &X, vector<int> &Y, vector<int> &R, int p, int r) {
    while (p < r) {
      int q = partition(X, Y, R, p, r);
      if (q - p < r - q) {
        // p -> q < q -> r
        sortCircles(X, Y, R, p, q - 1);
        p = q + 1;
      } else {
        sortCircles(X, Y, R, q + 1, r);
        r = q - 1;
      }
    }
  }
  int partition(vector<int> &X, vector<int> &Y, vector<int> &R, int p, int r) {
    int pivot = R[r];
    int i, j;
    for (i = p - 1, j = p; j < r ; j++) {
      if (R[j] < pivot) {
        i += 1;
        swap(R[i], R[j]);
        swap(X[i], X[j]);
        swap(Y[i], Y[j]);
      }
    }
    swap(R[r], R[i+1]);
    swap(X[r], X[i+1]);
    swap(Y[r], Y[i+1]);
    return i+1;
  }
  bool contain(int x, int y, int r, int px, int py) {
    if (disSquare(x, y, px, py) < r * r) {
      return true;
    } else {
      return false;
    }
  }
  int disSquare(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  }
};


int main(int argc, const char *argv[])
{
  
  return 0;
}
