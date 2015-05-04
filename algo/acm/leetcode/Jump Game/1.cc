
class Solution {
public:
    bool canJump(int A[], int n) {
        if (n <= 1) return true; // surely we can reach the first one
        int max_jump_so_far = A[0]; // the maximum index we can reach so far.
        for (int i = 1; i < n; i++) {
            if (max_jump_so_far >= i) {
                // if we can reach i based on current jumps
                max_jump_so_far = std::max(max_jump_so_far, i + A[i]);
            } else {
              return false;
            }
        }
        return max_jump_so_far >= (n-1);
    }
};
