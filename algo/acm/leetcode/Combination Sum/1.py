class Solution:
    # @param candidates, a list of integers
    # @param target, integer
    # @return a list of lists of integers
    def combinationSum(self, candidates, target):
        # Point: python's set is unordered. we need to sort it
        uniq_candidates = sorted(list(set(candidates)))
        print uniq_candidates
        
        ans = []
        self.recur(uniq_candidates, target, [], ans)
        return ans
    
    def recur(self, candidates, target, acc, ans):
        if target == 0 and acc:
            acc.reverse()
            ans.append(acc)
        elif not candidates or candidates[0] > target:
            return
        else:
            # Point: Pay special attention when a variable is mutable in recursive
            # operation
            last = candidates.pop()
            sel_times = target / last
            for i in xrange(0,sel_times+1):
                self.recur(candidates, target - i * last, acc + [last] * i, ans)
            # Point: Recover candidates
            candidates.append(last)


print Solution().combinationSum([8,7,4,3], 11) 
