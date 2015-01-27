#define SECK_DEBUG

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

#define N 50000
int A[N];
int n;

int max(int a, int b, int c) {
  return std::max(std::max(a,b), c);
}

#define INVALID_V INT_MAX
class Node {
 public:
  int max_sum;
  // range of Node is [u,v]
  int u_max_sum; // include u
  int v_max_sum; // include v
  int sum;
  Node() : max_sum(INVALID_V) {}
  bool invalid() const {
    return max_sum == INVALID_V;
  }
  // based on left child and right child value, update current node value
  void merge(const Node &lc, const Node &rc) {
    sum = lc.sum + rc.sum; // sum value of all values in current node.
    u_max_sum = std::max( // max sum value when including u
        lc.u_max_sum, // max sum value of left child when including u
        lc.sum + rc.u_max_sum // max sum value when not only including u, but also extend to right child
        );
    v_max_sum = std::max(rc.v_max_sum, rc.sum + lc.v_max_sum); // max sum value when including v
    max_sum = max(
        lc.max_sum, // left max sum
        rc.max_sum, // right max sum
        lc.v_max_sum + rc.u_max_sum // max sum including accross the middle value
        );
  }
};
#define LC(i) (((i)<<1)+1)
#define RC(i) (((i)+1)<<1)
Node nodes[4*N-1];
void updateSingleNode(Node &node, int v) {
  node.max_sum = node.u_max_sum = node.v_max_sum = node.sum = v;
}

void modify_rec(int nodeidx, int b, int e, int i, int v) {
  if (b == e) {
    // surely, b == e == i
    updateSingleNode(nodes[nodeidx], v);
    return;
  } else {
    int mid = (b+e)>>1;
    // We don't need to propage here since the node modifed are all leaves.
    // They don't have any child.
    if (i <= mid) {
      // left
      modify_rec(LC(nodeidx), b, mid, i, v);
    } else {
      modify_rec(RC(nodeidx), mid+1, e, i, v);
    }
    nodes[nodeidx].merge(nodes[LC(nodeidx)], nodes[RC(nodeidx)]);
  }
}

void modify(int pos, int v) {
  modify_rec(0, 0, n-1, pos, v);
}

// get max_sum in [i,j] and [b,e]
Node query_rec(int nodeidx, int b, int e, int i, int j) {
  if (e < i || b > j) {
    // not intersect
    return Node();
  } else if (i <= b && j >= e) {
    // [b,e] belong [i,j]
    return nodes[nodeidx];
  } else {
    int mid = (b+e)>>1;
    // intersect
    Node left = query_rec(LC(nodeidx), b, mid, i, j); // max sum in [b, mid] and [i,j]
    Node right = query_rec(RC(nodeidx), mid+1, e, i, j); // max sum in [mid+1, e] and [i,j]
    if (left.invalid()) return right;
    if (right.invalid()) return left;
    Node res;
    res.merge(left, right);
    return res;
  }
}

int query(int i, int j) {
  Node res = query_rec(0, 0, n-1, i, j);
  return res.max_sum;
}



void build_rec(int nodeidx, int b, int e) {
  if (b == e) {
    updateSingleNode(nodes[nodeidx], A[b]);
  } else {
    int mid = (b+e)>>1;
    build_rec(LC(nodeidx), b, mid);
    build_rec(RC(nodeidx), mid+1, e);
    nodes[nodeidx].merge(nodes[LC(nodeidx)],
                         nodes[RC(nodeidx)]);
  }
}

void build() {
  build_rec(0, 0, n-1);
}
void test_build(int i, int b, int e, int &max_i) {
  if (b == e) {
    max_i = std::max(i, max_i);
  } else {
    int mid = (b+e)>>1;
    test_build(LC(i), b, mid, max_i);
    test_build(RC(i), mid+1, e, max_i);
  }
}
int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif

  scanf("%d", &n);
  int max_i = 0;
  test_build(0, 0, n-1, max_i);
  cout << max_i << endl;
  return 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  build();
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int op, x, y;
    scanf("%d %d %d", &op, &x, &y);
    switch (op) {
      case 0:
        modify(x-1, y);
        break;
      case 1:
        printf("%d\n", query(x-1, y-1));
        break;
      default:
        break;
    }
  }

#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
