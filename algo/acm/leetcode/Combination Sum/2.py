
# My optimal solution for Combination Sum 2
# For this solution, we only need O(1) to chose one number. So total time
# complexity is O(number of unique combinations)

# The key idea to avoid duplicate is, when constructing one combination sum list,
# for duplicate numbers, we only select the first one appeared in the sorted list.
# If we didn't select the first one, then we will never select the rest ones since
# otherwise, it's conflicted with furture combination sum list that selects the first one.

class Solution:
    # @param candidates, a list of integers
    # @param target, integer
    # @return a list of lists of integers
    def combinationSum2(self, candidates, target):
        ans = []
        if not candidates:
            return ans
        
        candidates = sorted(candidates)
        last = candidates.pop()
        self.recur(candidates, last, False, target, [], ans)
        self.recur(candidates, last, True, target-last, [last], ans)
        return ans
        
    # @param prev, the number selected in last selection
    # @param selected, whether prev has been selected
    # @param acc, current accumulation of combination
    # @param ans, final combination list
    def recur(self, candidates, prev, selected, target, acc, ans):
        if target == 0:
            # make a copy of acc, since acc will be modifed in the future
            ans.append(list(reversed(acc)))
        if target < 0 or not candidates or candidates[0] > target:
            return

        last = candidates.pop()

        # not select
        self.recur(candidates, last, False, target, acc, ans)
        if last == prev and not selected:
            # remove duplicates.
            # If current number is equal to previous selected number and
            # prev is not selected, then we won't select the number to avoid
            # duplicates.
            candidates.append(last)
            return
        
        # select once
        acc.append(last)
        self.recur(candidates, last, True, target - last, acc, ans)
        acc.pop()
        
        candidates.append(last)
        

print Solution().combinationSum2([10,1,2,7,6,1,5], 8)
