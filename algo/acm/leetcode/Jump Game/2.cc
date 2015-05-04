/*
 *  My first idea on how to solve this problem is to use dp with:
 * 
 *  max_jump_so_far[k]: the maximum index we can reach in k jumps
 *
 *  Then we can solve it in O(n^2) since k < n.
 *  for index i:
 *    max_jump_so_far[k+1] = max(max_jump_so_far[k+1], i+A[i]) as long as max_jump_so_far[k] >= i(i.e., we can reach i in k steps)
 *  
 *  Based on this idea,
 *  we can optimize this.
 *
 *  First, we move k to the outer for loops since we want minimum k, so we can break once we reach the destination in k steps
 *
 *  for k steps:
 *    for i in [0, max_jump_so_far[k-1]]: // we enumerate every index we can cover in k-1 steps to see where we can reach in k steps
 *      max_jump_so_far[k] = max(max_jump_so_far[k], i+A[i])
 *    if max_jump_so_far[k] >= n-1: return k
 *
 *  Second, we can further optimize this. If we have already considered [0, max_jump_so_far[k-1]], we don't need to recalculate it
 *  in the future. For the next loop, we only need to consider (max_jump_so_far[k-1], max_jump_so_far[k]]
 */

#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int jump(int A[], int n) {
        if (n <= 1) return 0; // we don't need to jump to reach the end point.
        
        int covered_idx = 0; // the index we have covered
        int prev_max_jump_so_far = A[0]; // the next max index we are gonna cover
        int steps = 1; // we need to jump "steps" to reach prev_max_jump_so_far
        do {
            if (prev_max_jump_so_far <= covered_idx) return 0; // We failed to extend the index we are gonna considering in the previous loop, it means we can't make any move further.
            if (prev_max_jump_so_far >= n-1) return steps; // if we have alread reached the final point, we break directly
            int cur_max_jump_so_far = prev_max_jump_so_far; // max jump in "steps+1" steps
            steps += 1;
            for (int i = covered_idx+1; i <= prev_max_jump_so_far; i++) {
                cur_max_jump_so_far = std::max(cur_max_jump_so_far, i + A[i]);
            }
            covered_idx = prev_max_jump_so_far; // update covered idx
            prev_max_jump_so_far = cur_max_jump_so_far; // update the max index we are gonna cover in the next loop
        } while (steps < n);
        return 0;
    }
};

int main() {
  int A[] = {};
  cout << Solution().jump(A, 5) << endl;
  return 0;
}
