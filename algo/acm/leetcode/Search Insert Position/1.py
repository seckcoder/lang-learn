class Solution:
    # @param A, a list of integers
    # @param target, an integer to be inserted
    # @return integer
    def searchInsert(self, A, target):
        p = 0;
        r = len(A)-1
        mark = 0
        while p <= r:
            m = (p+r) / 2
            if A[m] < target:
                mark = m + 1
                p = m + 1
            elif A[m] > target:
                r = m - 1
            else:
                return m
        return mark
            
            
        
