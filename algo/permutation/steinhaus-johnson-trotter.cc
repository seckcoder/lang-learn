/* The steinhaus-johnson-trotter algorithm to generate all permutations
   of a list


   General Procedure:

    Initialize the first permutation with <1 <2 ... <n
    while there exists a mobile integer
      find the largest mobile integer k
      swap k and the adjacent integer it is looking at
      reverse the direction of all integers larger than k


   Time complexity:
    

   Intuition and Proof:





*/


#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


#define LEFT_DIR false
#define RIGHT_DIR true

class PermutationIter {
  public:
    size_t size;
    vector<int> vals;
    vector<bool> dirs;
    PermutationIter(size_t n) {
      assert(n > 0);
      size = n;
      vals.resize(size);
      dirs.resize(size);
      for (int i = 0; i < size; i++) {
        vals[i] = i;
        dirs[i] = LEFT_DIR;
      }
    }
    void first(vector<int> &vec) {
      vec.resize(size);
      copyVals(vec);
    }
    void copyVals(vector<int> &output) {
      std::copy(vals.begin(), vals.end(), output.begin());
    }
    bool next(vector<int> &vec) {
      std::find(
      for (int i = size; i >= 1; i--) {
        val.index
      }
    }
};


template <class T>
void printVec(const vector<T> &vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

int main() {
  PermutationIter iter(4);

  vector<int> perm;
  while (iter.next(perm)) {
    printVec(perm);
  }
}
