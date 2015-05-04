class Solution:
    # @param A, a list of integers
    # @param target, an integer to be searched
    # @return a list of length 2, [index1, index2]
    def searchRange(self, A, target):
        index1 = self.searchSmallestIndex(A, target)
        index2 = self.searchLargestIndex(A, target)
        return [index1, index2]
    
    def searchSmallestIndex(self, A, target):
        p = 0;
        r = len(A) - 1
        mark = -1
        
        while p <= r:
            m = (p+r)/2
            
            if A[m] < target:
                p = m + 1
            elif A[m] > target:
                r = m - 1
            else:
                mark = m
                r = m - 1
        return mark
    
    def searchLargestIndex(self, A, target):
        p = 0
        r = len(A) - 1
        mark = -1
        
        while p <= r:
            m = (p+r)/2
            
            if A[m] < target:
                p = m + 1
            elif A[m] > target:
                r = m - 1
            else:
                mark = m
                p = m + 1
        return mark
        
