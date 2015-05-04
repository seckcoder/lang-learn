
class Solution1:
    # @param A, a list of integers
    # @return an integer
    # this is a wrong solution for the test cases given at leetcode.
    # But it works when we consider the minimum to be 1
    def maxProduct(self, A):
        if not A: return 1
        
        min_v = 1;
        max_v = 1
        final_ans = 1
        for v in A:
            if v > 0:
                max_v = v * max_v
                min_v = min(v * min_v, 1)
            else:
                temp_max_v = max_v
                max_v = max(v * min_v, 1)
                min_v = v  * temp_max_v
            final_ans = max(max_v, final_ans)
        return final_ans


class Solution:
    def maxProduct(self, A):
        if not A: return 1
        min_v = A[0]
        max_v = A[0]
        final_ans = max_v

        for v in A[1:]:
            if v > 0:
                max_v = max(v * max_v, v)
                min_v = min(v * min_v, v)
            else:
                temp_max_v = max_v
                max_v = max(v * min_v, v)
                min_v = min(v * temp_max_v, v)
            final_ans = max(max_v, final_ans)
        return final_ans


print Solution().maxProduct([-4,-3,-2])
