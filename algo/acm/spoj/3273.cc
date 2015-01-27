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



#define N 200000
int q;
int A[N];
char op[N];
int intvn;

#define LC(i) (((i)<<1)+1)
#define RC(i) (((i)+1)<<1)

/*
 * basic Idea:
 * For each node of segment tree, we store number of elements appeared in
 * the range. The input number can be very large, so we compress it to fit 
 * into range of segment tree by maintaining a mapping between values and index.
 * The mapping is built by count values inserted(I), deleted(D) and counted(C).
 *  - Insert and Delete correspond to modify operation of segment tree. After inserting/deleting a value, we modify the leaf node correspond to the value. 
 *  - Querying k-th smallest, we use binary search based on number elements
 *  in range.
 *  - Count number elements smaller thant some value, we first get the index of the value
 *  then this is as simple as querying number elements in [0, index]
 */ 

class Node {
 public:
  int v; // number of elements in the interval.
  void merge(const Node &n1, const Node &n2) {
    v = n1.v + n2.v;
  }
};

Node nodes[4*N-1];
template <void (*fn)(Node &n)>
void modify(int ni, int b, int e, int i) {
  if (b == e) {
    fn(nodes[ni]);
    return; 
  } else {
    int mid = (b+e)>>1;
    // we don't need to propagate since both methods of modifying segment tree
    // only change leaf node.
    if (i <= mid) {
      modify<fn>(LC(ni), b, mid, i);
    } else {
      modify<fn>(RC(ni), mid+1, e, i);
    }
    nodes[ni].merge(nodes[LC(ni)], nodes[RC(ni)]);
  }
}

// return total number of elements in [b,e] and [i,j]
int query(int ni, int b, int e, int i, int j) {
  if (j < b || e < i) {
    return 0;
  } else if (i <= b && j >= e) {
    return nodes[ni].v;
  } else {
    int mid = (b+e) >> 1;
    return query(LC(ni), b, mid, i, j) +
        query(RC(ni), mid+1, e, i, j);
  }
}

int binSearch(int ni, int b, int e, int v) {
  int acc = 0;
  while (b < e) {
    int mid = (b+e)>>1;
    //cout << b << " " << e << " " << acc << " " << nodes[LC(ni)].v << endl;
    if (acc + nodes[LC(ni)].v >= v) {
      // go left
      ni = LC(ni);
      e = mid;
    } else {
      // go right
      acc += nodes[LC(ni)].v;
      ni = RC(ni);
      b = mid + 1;
    }
  }
  return b;
}

void inc(Node &n) {
  n.v = 1;
}
void del(Node &n) {
  n.v = 0;
}
void build(int ni, int b, int e, int tmp_A[]) {
  if (b == e) {
    nodes[ni].v = 0;
  } else {
    int mid = (b+e)>>1;
    build(LC(ni), b, mid, tmp_A);
    build(RC(ni), mid+1, e, tmp_A);
    nodes[ni].merge(nodes[LC(ni)], nodes[RC(ni)]);
  }
}


int main(int argc, const char *argv[])
{
  
#ifdef SECK_DEBUG
  freopen("test.in", "r", stdin);
#endif
  scanf("%d", &q);
  int tmp_A[N];
  intvn = 0;
  for (int i = 0; i < q; i++) {
    scanf("%*[ \n\t]%c %d", &op[i], &A[i]);
    switch (op[i]) {
      case 'I':
      case 'D':
      case 'C':
        tmp_A[intvn] = A[i];
        intvn += 1;
        break;
    }
  }
  /*
   * tmp_A: store count elements (uniquely)
   * qmap: (value in A , order of the value in A)
   *       So qmap is used to map value to an index starting from 0. 
   */
  std::sort(tmp_A, tmp_A+intvn);
  int *end = std::unique(tmp_A, tmp_A+intvn);
  intvn = end - tmp_A;
  std::map<int, int> qmap;
  for (int i = 0; i < intvn; i++) {
    qmap.insert(std::pair<int, int>(tmp_A[i], i));
  }
  build(0, 0, intvn-1, tmp_A);

  for (int i = 0; i < q; i++) {
    int mapped_v, k;
    switch (op[i]) {
      case 'I':
        mapped_v = qmap[A[i]];
        // insert
        modify<inc>(0, 0, intvn-1, mapped_v);
        break;
      case 'D':
        mapped_v = qmap[A[i]];
        modify<del>(0, 0, intvn-1, mapped_v);
        // delete
        break;
      case 'K':
        k = A[i];
        // k-th smallest
        if (query(0, 0, intvn-1, 0, intvn-1) < k) {
          // if total number of elements is small than k
          printf("invalid\n");
        } else {
          //cout << query(0, 0, intvn-1, 2, 2) << endl;
          //cout << qmap[2] << " " << query(0, 0, intvn-1, 0, intvn-1) << endl;
          int idx = binSearch(0, 0, intvn-1, k);
          printf("%d\n", tmp_A[idx]);
        }
        break;
      case 'C':
        // count
        mapped_v = qmap[A[i]];
        if (mapped_v == 0) {
          printf("0\n");
        } else {
          printf("%d\n", query(0, 0, intvn-1, 0, mapped_v-1));
        }
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
