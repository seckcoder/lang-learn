#include <vector>
using namespace std;
// Naive solution.
// 
// Basic Idea:
//  
//  tryNext: if exist next permutation, replace it in place, and return true.
//           otherwise, return false.
//
//  When next permutation not exist?
//    - when the list is sorted non-increasingly.
//  Otherwise, the next permutation exist.
//
//  What's the next permutation?
//    - Define pivot = max{i, num[i:] exists the next permutation}
//      define new_pivot = argmin(num[i] > num[pivot])
//      Then new_pivot is the new first number, and num[i+1:] still doesn't have
//      next permutation
//  
// O(n^2) time complexity
class Solution1 {
public:
    typedef vector<int>::iterator ITER;
    void nextPermutation(vector<int> &num) {
        if (tryNext(num.begin(), num.end())) {
            return;
        } else {
            //std::sort(num.begin(), num.end());
            std::reverse(num.begin(), num.end());
        }
    }
    bool tryNext(ITER begin, ITER end) {
        if (begin == end) return false;
        ITER max_elem_it = std::max_element(begin, end);
        if (*max_elem_it == *begin) {
            return tryNext(begin+1, end);
        } else {
            if (tryNext(begin+1, end)) {
                return true;
            } else {
                // find new_pivot
                ITER smallest_greater_it = findSmallestGreater(begin+1, end, *begin);
                // assert smallest_greater_it != begin and smallest_greater_it != end
                // swap pivot wit new_pivot
                std::swap(*begin, *smallest_greater_it);
                //std::sort(begin+1, end);
                std::reverse(begin+1,end);
                return true;
            }
        }
    }
    ITER findSmallestGreater(ITER begin, ITER end, int v) {
        while (begin != end && *begin > v) {
            begin++;
        }
        return begin-1;
    }
};

// O(n) solution
class Solution {
  public:
    typedef vector<int>::iterator Iter;
    // find the last point that the permutation exist
    // i.e., find last i, such that num[i:] exist next permutation
    Iter findLastNextPermutationExist(Iter tail, Iter until) {
      while (tail >= until && (*tail) >= *(tail+1)) {
        tail--;
      }
      return tail;
    }
    void nextPermutation(vector<int> &num) {
      if (num.size() <= 1) return;
      Iter begin = findLastNextPermutationExist(num.end()-2, num.begin());
      if (begin < num.begin()) {
        // permutation not exist
        std::reverse(num.begin(), num.end());
      } else {
        // do a permutation swapping
        Iter smallest_greater_it = findSmallestGreater(begin+1, num.end(), *begin);
        std::swap(*begin, *smallest_greater_it);
        std::reverse(begin+1, num.end());
      }
    }
    Iter findSmallestGreater(Iter begin, Iter end, int v) {
      while (begin != end && *begin > v) {
        ++begin;
      }
      return begin-1;
    }
};
