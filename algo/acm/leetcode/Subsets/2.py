# Let me work out this process a little bit:

# Recursive procedure:
# subsets = combine(A[0], subsets(A[1:]))
# How to combine to avoid duplicates?
# An example:
#    [1,2,2]
#
# for combine(1,[2,2]), apparently no duplicates will be generated.
# So we can guess we need A[0] < A[1]
# for combine(2,[2]), if we implement combine like 1
#   2 [] -> [], [2]
#   2 [2] -> [2], [2,2]

# This example is not quite clear
# for combine(2,[2,3])
#   2 [] -> [], [2]
#   2 [2] -> [2], [2,2]
#   2 [3] -> [3], [2,3]
#   2 [2,3] -> [2,3], [2,2,3]

# Let a = A[0], B being a subset of A[1:]
# if B is empty
#    1) Add B is necessary and won't cause conflict, since we have added nothing to the subsets
#    2) Add a:B is necessary won't cause conflict, since a:B != []
# if a != B[0]
#    3) Add B is necessary and won't cause conflict. 
#           We have only added [] and [a] sets by the previous condiction.(B != [a])
#    4) Add a:B[0] is necessary and won't cause conflict
#           Same idea by considering what we have already added.
#    
# Let's checkout the most complicate case in the end.
# elif a = B[0]
#    add B[0] may cause conflict with 2),4).
#    add a:B[0] won't cause conflict with previous cases.



class Solution:
    # @param num, a list of integer
    # @return a list of lists of integer
    def subsetsWithDup(self, S):
        S.sort()
        return self.subsetsWithDupRec(S)
    
    def subsetsWithDupRec(self, S):
        if not S: return [[]]
        
        smallest = S[0]
        sets = []
        for sub_set in self.subsetsWithDupRec(S[1:]):
            if not sub_set:
                sets.append(sub_set)
                sets.append([smallest])
            elif smallest != sub_set[0]:
                sets.append(sub_set)
                sets.append([smallest] + sub_set)
            else:
                sets.append([smallest] + sub_set)
        return sets
