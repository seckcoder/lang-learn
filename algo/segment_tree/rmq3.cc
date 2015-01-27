#include <cstdlib>


#include <iostream>
using std::cout;
using std::endl;

struct RMQ {
  int *A;
  int alen;


  // processed
  int *M;
  int mlen;
};

#define LC(i) (((i)<<1)+1)
#define RC(i) (((i)<<1)+2)


void mergeNode(int nix, int *A, int *M) {
  int left = M[LC(nix)],
      right = M[RC(nix)];
  if (A[left] < A[right]) M[nix] = left;
  else M[nix] = right;
}

void preprocessRecur(int nix, int *A, int *M,
    int p, int r) {
  if (p == r) {
    M[nix] = p;
  } else {
    int mid = (p+r)>>1;
    preprocessRecur(LC(nix), A, M, p, mid);
    preprocessRecur(RC(nix), A, M, mid+1, r);
    mergeNode(nix, A, M);
  }
}

void preprocess(RMQ &rmq) {
  int *A = rmq.A,
      n = rmq.alen,
      mlen = 4*n-1; // length of M
  int *M = (int *)malloc(mlen * sizeof(int));
  
  preprocessRecur(0, A, M, 0, n-1);
  rmq.M = M;
  rmq.mlen = mlen;
}

// minimum element in [b,e] and [p,r]
// b,e represents range of current node nix
// Note the range length of [b,e] and [p,r] is different!
int queryRec(int *A, int *M, int nix, int b, int e, int p, int r) {
  if (p > e || r < b) return -1; // not intersect
  if (p <= b && e <= r) {
    //cout << M[nix] << endl;
    return M[nix];
  }
  int mid = (b+e)>>1;
  int left = queryRec(A, M, LC(nix), b, mid, p, r);
  int right = queryRec(A, M, RC(nix), mid+1,e, p,r);
  if (left == -1) return right;
  else if (right == -1) return left;
  else if (A[left] < A[right]) return left;
  else return right;
}
int query(RMQ &rmq, int p, int r) {
  return queryRec(rmq.A, rmq.M, 0, 0, rmq.alen-1, p, r);
}


int main() {
  RMQ rmq;
  int A[] = {2,4,3,1,6,7,8,9,1,7};
  rmq.A = A;
  rmq.alen = 10;
  preprocess(rmq);
  std::cout << query(rmq, 2,7) << std::endl;
  std::cout << query(rmq, 1,1) << std::endl;
  return 0;
}
