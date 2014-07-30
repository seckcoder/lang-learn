#include <algorithm>

// range: 0->(N-1)
#define N 100
#define IMPOSSIBLE_V -1
// at most 2*N-1 nodes
//int A[N];
class Node {
 public:
  int v;
  int add;
  Node(): add(0) {}
  void merge(const Node &n1, const Node &n2) {
    v = std::min(n1.v, n2.v);
    add = 0;
  }
  void update(int newv) {
    v = newv;
    add = 0;
  }
  void propagate(Node &n1, Node &n2) {
    n1.add += add;
    n1.v += add;
    n2.add += add;
    n2.v += add;
    add = 0;
  }
};

Node nodes[4*N-1];

// left child
#define LC(i) (((i)<<1)+1)
// right child
#define RC(i) (((i)+1)<<1)
// parent
#define PAR(i) (((i)-1)>>1)


void build(int nodeidx, int left, int right, int A[]) {
  if (left == right) {
    nodes[nodeidx].update(A[left]);
  } else {
    build(LC(nodeidx), left, (left+right)>>1, A);
    build(RC(nodeidx), ((left+right)>>1)+1, right, A);
    nodes[nodeidx].merge(nodes[LC(nodeidx)], nodes[RC(nodeidx)]);
  }
}
// A[i] = v. nodeidx is the current node we are processing
void modify(int nodeidx, int left, int right, int i, int v) {
  if (left == right) {
    nodes[left].update(v);
    return ;
  } else {
    nodes[nodeidx].propagate(nodes[LC(nodeidx)], nodes[RC(nodeidx)]);
    if (left <= i && i <= right) {
      // modify left
      modify(LC(nodeidx), left, right, i, v);
    } else {
      // modify right
      modify(RC(nodeidx), left, right, i, v);
    }
    nodes[nodeidx].merge(nodes[LC(nodeidx)], nodes[RC(nodeidx)]);
  }
}

// lookup the mini value in [left-right] ⋂ [node.u,node.v] of A
int query(int nodeidx, int b, int e, int i, int j) {
  if (e < i ||
      b > j) {
    return IMPOSSIBLE_V;
  }
  // belongs to
  if (i >= b &&
      j <= e) {
    return nodes[nodeidx].v;
  }
  nodes[nodeidx].propagate(nodes[LC(nodeidx)], nodes[RC(nodeidx)]);

  int mid = (b+e)>>1;
  int left_v = query(LC(nodeidx), b, mid, i, j);
  int right_v = query(RC(nodeidx), mid+1, e, i, j);

  if (left_v == IMPOSSIBLE_V) return right_v;
  if (right_v == -1) return left_v;
  if (left_v <= right_v ) return left_v;
  return right_v;
}
