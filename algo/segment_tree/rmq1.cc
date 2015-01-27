#include <vector>
#include <cmath>
#include <cassert>
#include <limits>
using std::vector;


// debuging...
#include <iostream>
using std::cout;
using std::endl;

/*
 * <O(n), O(sqrt(n))> range minimum query implementation
 * Basic idea: the array A is split into multiply blocks, with each
 * has size floor(sqrt(n))
 */

struct RMQ {
  int *A; // array to query
  int alen; // length of the array

  // preprocessed //
  int *M; // used to store the index of minimum value in each block 
  int mlen; // length of M
  int bs; // block size
};

void preprocess(RMQ &rmq) {
  int *A = rmq.A;
  int n = rmq.alen;
  int bs = int(std::floor(std::sqrt(n))); // block size
  int mlen = int(std::ceil(float(n)/bs)); // number of blocks
  int *M = (int*)malloc(rmq.mlen*sizeof(int));
  std::fill(M, M+mlen, -1);
  assert(M != NULL);
  for (int i = 0; i < mlen; i += 1) {
    int base_i = i * bs;
    // initialize block i
    for (int j = base_i; j < std::min(base_i+bs, n); j++) {
      if (M[i] == -1 || A[M[i]] > A[j]) {
        M[i] = j;
      }
    }
  }

  rmq.M = M;
  rmq.mlen = mlen;
  rmq.bs = bs;
}

// query minimum value in [p,r]
int query(const RMQ &rmq, int p, int r) {
  /*
   * For example:
   * [b0  p  e0][b1  e1] ... [bk r ek]
   *
   * [bi ei] represents block i
   * Then start_block = 1, end_block = k
   *
   */
  int bs = rmq.bs,
      *A = rmq.A,
      *M = rmq.M,
      start_block = std::ceil((float)p/bs), // the first complete block in [p,r]
      end_block = r / bs, // the last block(which may not be complete) index in [p,r]
      min_i = p;
  if (start_block < end_block) {
    // [p,r] contains at least one block
    int b1 = start_block * bs, // starting index in A of first block
        bk = end_block * bs; // starting index in A of last block
    // [p, b1)
    for (int i = p; i < b1; i++) {
      if (A[i] < A[min_i]) {
        min_i = i;
      }
    }

    // [b1, bk)
    for (int bi = start_block; bi <= end_block; bi++) {
      if (A[M[bi]] < A[min_i]) {
        min_i = M[bi];
      }
    }
    // [bk, r]
    for (int j = bk; j <= r; j++) {
      if (A[j] < A[min_i]) {
        min_i = j;
      }
    }
  } else {
    // [p,r] is in a block
    for (int i = p; i <= r; i++) {
      if (A[i] < A[min_i]) min_i = i;
    }
  }
  return min_i;
}


int main() {
  RMQ rmq;
  int A[] = {2,4,3,1,6,7,8,9,1,7};
  rmq.A = A;
  rmq.alen = 10;
  preprocess(rmq);
  for (int i = 0; i < rmq.mlen; i++) {
    cout << rmq.M[i] << " ";
  }
  cout << endl;
  std::cout << query(rmq, 2,7) << std::endl;
  std::cout << query(rmq, 1,1) << std::endl;
  return 0;
};
