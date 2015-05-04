

# One pass, Constant Space

class Solution:
    # @param A a list of integers
    # @return nothing, sort in place
    def sortColors(self, A):
        red_idx = 0
        cur = 0
        blue_idx = len(A)-1
        # Loop Invariant:
        # [0,red_idx) : red
        # [red_idx, cur) : white
        # (blue_idx, n) : blue
        while cur <= blue_idx:
            if A[cur] == 0:
                A[red_idx], A[cur] = A[cur], A[red_idx]
                red_idx += 1
                cur += 1
            elif A[cur] == 1:
                cur += 1
            else:
                A[cur], A[blue_idx] = A[blue_idx], A[cur]
                blue_idx -= 1
