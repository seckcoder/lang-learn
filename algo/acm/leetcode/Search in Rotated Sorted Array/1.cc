#include <iostream>
using namespace std;


#define LEFT -1
#define RIGHT 1
#define EQUAL 0

// array sorted mono decreasing
int cmp_greater(int cur, int target) {
    if (cur < target) return LEFT;
    if (cur > target) return RIGHT;
    return EQUAL;
}

// array sorted mono increasing
int cmp_less(int cur, int target) {
    if (cur < target) return RIGHT;
    if (cur > target) return LEFT;
    return EQUAL;
}


class Solution {
public:
    int search(int A[], int n, int target) {
        if (n == 0) return -1;
        if (n == 1 && A[0] == target) return 0;
        if (n == 1) return -1;
        // n >= 2
        int p = 0, r = n-1;
        int mark = -1;
        
        while (p <= r) {
            int m = (p+r)/2;
            if (A[m] <= A[n-1]) {
                mark = m;
                r = m - 1;
            } else if (A[m] > A[n-1]) {
                p = m + 1;
            }
        }
        if (mark == -1) {
            // array is sorted in decreasing order
            return binSearch(A, 0, n-1, target, cmp_greater);
        } else {
            int part1 = binSearch(A, 0, mark-1, target, cmp_less);
            int part2 = binSearch(A, mark, n-1, target, cmp_less);
            if (part1 != -1) return part1;
            if (part2 != -1) return part2;
            return -1;
        }
    }
    template <class Function>
    int binSearch(int A[], int p, int r, int target, Function cmp) {
        while (p <= r) {
            int m = (p+r) / 2;
            if (cmp(A[m], target) == LEFT) {
                r = m - 1;
            } else if (cmp(A[m], target) == RIGHT) {
                p = m + 1;
            } else {
                return m;
            }
        }
        return -1;
    }
};

int main() {
  int A[] = {3,5,1};
  cout << Solution().search(A, 3, 3) << endl;
  return 0;
}
