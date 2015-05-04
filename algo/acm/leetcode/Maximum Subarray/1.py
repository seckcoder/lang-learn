class Solution:
    # @param A, a list of integers
    # @return an integer
    def maxSubArray(self, A):
        if not A: return 0
        max_v = A[0]
        final_ans = A[0]
        for v in A[1:]:
            max_v = max(v, v + max_v)
            final_ans = max(final_ans, max_v)
        return final_ans
