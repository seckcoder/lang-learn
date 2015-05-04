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
                
