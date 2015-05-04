class Solution:
    # @param S, a list of integer
    # @return a list of lists of integer
    def subsets(self, S):
        S.sort()
        return self.subsetsRec(S)
    
    def subsetsRec(self, S):
        if not S: return [[]]
        
        smallest = S[0]
        sets = []
        for sub_set in self.subsetsRec(S[1:]):
            sets.append(sub_set)
            sets.append([smallest] + sub_set)
        return sets
        
        
        
        
    
    
        
