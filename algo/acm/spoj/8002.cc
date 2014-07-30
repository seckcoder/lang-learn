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
#define LC(i) (((i)<<1)+1)
#define RC(i) (((i)+1)<<1)
//#define INVALID_V 0

class Node {
 public:
  int64 sum;
  int64 add;
  Node():sum(0), add(0) {}
  void init() {
    sum = 0;
    add = 0;
  }
  void merge(const Node &n1, const Node &n2) {
    sum = n1.sum + n2.sum;
    add = 0; // why add=0 here? During build, we need to set add to 0.
  }
  void addValue(int b, int e, int64 v) {
    add += v;
    sum += v*(e-b+1);
  }
  void propagate(Node &n1, int n1_b, int n1_e,
                 Node &n2, int n2_b, int n2_e) {
    n1.addValue(n1_b, n1_e, add);
    n2.addValue(n2_b, n2_e, add);
    //merge(n1, n2); nodes is already updated, we don't need to merge again.
    add = 0;
  }
};

#define M 4*N-1
Node nodes[M];

void build(int ni, int b, int e) {
  if (b == e) {
    nodes[ni].init();
  } else {
    int mid = (b+e)>>1;
    build(LC(ni), b, mid);
    build(RC(ni), mid+1, e);
    nodes[ni].merge(nodes[LC(ni)], nodes[RC(ni)]);
  }
}

// assumption of lazy propagation: 
//  For the current node in processing, sum is always the right sum.
int64 query(int ni, int b, int e, int i, int j) {
  // not intersect
  if (e < i || b > j) return 0;
  if (i <= b && e <= j) {
    // according to the assumption, nodes[ni].sum is always the right sum
    return nodes[ni].sum;
  }
  int mid = (b+e)>>1;
  nodes[ni].propagate(nodes[LC(ni)], b, mid,
                      nodes[RC(ni)], mid+1, e);
  // the propagate procedure makes sure that LC(ni), RC(ni) has the right sum.
  int64 left = query(LC(ni), b, mid, i, j);
  int64 right = query(RC(ni), mid+1, e, i, j);
  return left + right;
}

void addRange(int ni, int b, int e, int i, int j, int v) {
  if (e < i || b > j) return ;
  if (i <= b && e <= j) {
    // addValue makes sure the current node in processing has the right
    // sum after addRange operation.
    nodes[ni].addValue(b, e, v);
    return ;
  }
  int mid = (b+e)>>1;
  // first propagte the prevous lazy addition.
  nodes[ni].propagate(nodes[LC(ni)], b, mid,
                      nodes[RC(ni)], mid+1, e);
  // process the current lazy addition.
  addRange(LC(ni), b, mid, i, j, v);
  addRange(RC(ni), mid+1, e, i, j, v);
  nodes[ni].merge(nodes[LC(ni)], nodes[RC(ni)]);
}


int main(int argc, const char *argv[])
{
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  int t;
  scanf("%d", &t);
  while (t>=1) {
    t -= 1;
    int n, c;
    scanf("%d %d", &n, &c);
    build(0, 0, n-1);
    for (int i = 0; i < c; i++) {
      int op, p, q, v;
      scanf("%d", &op);
      switch (op) {
        case 0:
          // add
          scanf("%d %d %d", &p, &q, &v);
          addRange(0, 0, n-1, p-1, q-1, v);
          break;
        case 1:
          // query
          scanf("%d %d", &p, &q);
          cout << query(0, 0, n-1, p-1, q-1) << endl;
          break;
        default:
          break;
      }
    }
  }
#ifdef SECK_DEBUG
  cerr << "\nTime = " << 1000* (double(clock()) / CLOCKS_PER_SEC) << "ms" << endl;
#endif
  return 0;
}
