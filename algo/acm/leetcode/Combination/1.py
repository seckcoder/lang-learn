class Solution:
    # @return a list of lists of integers
    def combine(self, n, k):
        if k == 0: return [[]]
        if n == k: return [range(1,n+1)]
        
        not_select = self.combine(n-1,k)
        select = self.combine(n-1,k-1)
        for lst in select:
            lst.append(n)
        not_select.extend(select)
        return not_select
    

print Solution().combine(4,2)
