//#define SECK_DEBUG

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <algorithm>
#include <set>
#include <string>
#include <iomanip>
#include <cmath>
#include <map>
#include <functional>
#include <climits>
#include <cstdio>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::cin;
using std::string;
using std::map;
using std::cerr;
using std::ostream;
using std::istream;


#define PI 3.14159265359
#define IS_ODD(v) ((v) & 1)
//#define IS_EVEN(v) (((v) - (((v) >> 1) << 1)) == 0)
typedef long long int int64;
typedef unsigned char uint8;

ostream &operator<<(ostream &os, const uint8 v) {
  os << (int)v;
  return os;
}

istream &operator>>(istream &is, uint8 &v) {
  int tmp;
  is >> tmp;
  v = (uint8)tmp;
  return is;
}

inline uint8 min(uint8 a, uint8 b) {
  return (a<b)?a:b;
}
inline uint8 max(uint8 a, uint8 b) {
  return (a>b)?a:b;
}

// a,b could be negative
// it always return positive remainder.
int pmod(int a, int b) {
  if (b < 0) {
    return pmod(-a, -b);
  }
  int ret = a % b;
  if (ret < 0) ret += b;
  return ret;
}

#define N 100000
#define LOGN 18


template <class Compare>
void buildRMQ(const int arr[], const int n,
              int M[N][LOGN], Compare comp) {
  // init
  for (int i = 0; i < n; i++) {
    // j = 0
    M[i][0] = i;
  }

  for (int j = 1; (1 << j) <= n; j++) {
    for (int i = 0; i + (1<<j) - 1 < n; i++) {
      if (comp(arr[M[i][j-1]], arr[M[i+(1<<(j-1))][j-1]])) {
        M[i][j] = M[i][j-1];
      } else {
        M[i][j] = M[i+(1<<(j-1))][j-1];
      }
    }
  }
}


int mini[N][LOGN];
int maxi[N][LOGN];
class RMQ {
 public:
  const int* arr;
  RMQ(const int harr[], const int n) {
    arr = harr;
    // build rmq
    buildRMQ(arr, n, mini, std::less<int>());
    buildRMQ(arr, n, maxi, std::greater<int>());
  }
  int minQ(int i, int j) const {
    return Q(i, j, mini, std::less<int>());
  }
  int maxQ(int i, int j) const {
    return Q(i, j, maxi, std::greater<int>());
  }
  template <class Compare>
  int Q(int i, int j, int M[N][LOGN], Compare comp) const {
    int k = std::floor(log2(j-i+1));
    //cout << i << " " << j-(1<<k)+1 << " " << k << endl;
    if (comp(arr[M[i][k]], arr[M[j-(1<<k)+1][k]])) {
      return M[i][k];
    } else {
      return M[j-(1<<k)+1][k];
    }
  }
  int diffQ(int i, int j) const {
    return arr[maxQ(i, j)] - arr[minQ(i, j)];
  }
};

class IdxPair {
 public:
  int i,j;
  IdxPair() {}
  IdxPair(int hi, int hj):i(hi), j(hj) {}
};

int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  int n, k;
  scanf("%d %d", &n, &k);
  int h[N];
  for (int i = 0; i < n; i++) {
    scanf("%d", &h[i]);
  }
  RMQ rmq(h, n);
  vector<IdxPair> indexes;
  int left = 0, right = 0;
  int max_books_num = 0;
  while (left < n && right < n) {
    // assert left <= right
    while (right < n && rmq.diffQ(left, right) <= k) {
      //cout << left << " " << right << " " << rmq.diffQ(left, right) << endl;
      right += 1;
    }
    if (right - left > max_books_num) {
      max_books_num = right - left;
      indexes.clear();
      indexes.push_back(IdxPair(left, right-1));
    } else if (right - left == max_books_num) {
      indexes.push_back(IdxPair(left, right - 1));
    }
    if (right >= n) {
      break;
    }
    while (left < n && left <= right && rmq.diffQ(left, right) > k) {
      left += 1;
    }
  }
  cout << max_books_num << " " << indexes.size() << endl;
  for (int i = 0; i < indexes.size(); i++) {
    cout << indexes[i].i + 1 << " " << indexes[i].j + 1 << endl;
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
