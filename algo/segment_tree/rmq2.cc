

#include <algorithm>
#include <cmath>
#include <cassert>


#include <iostream>
using std::cout;
using std::endl;

struct RMQ {
  int *A;
  int alen;


  // processed

  int **M; // M[i][j]: starting from i, 2^j number of elements.
};


void preprocess(RMQ &rmq) {
  int *A = rmq.A,
      n = rmq.alen;
  assert(n > 0);
  int **M = (int **)malloc(n * sizeof(int*));
  M[0] = (int *)malloc(n * int(std::floor(log2(n))+1));
  M[0][0] = 0;
  for (int i = 1; i < n; i++) {
    M[i] = M[i-1] + n;
    M[i][0] = i;
  }

  for (int j = 1; (1<<j) <= n; j++) {
    for (int i = 0; i + (1<<j) - 1 < n; i++) {
      int left = M[i][j-1],
          right = M[i+(1<<(j-1))][j-1];

      if (A[left] < A[right]) M[i][j] = left;
      else M[i][j] = right;
    }
  }
  rmq.M = M;
}


int query(const RMQ &rmq, int p, int r) {
  int *A = rmq.A,
      **M = rmq.M;
  int k = std::floor(log2(r-p+1));
  int left = M[p][k],
      right = M[r-(1<<k)+1][k];
  if (A[left] < A[right]) return left;
  else return right;
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
