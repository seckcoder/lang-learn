
# Use insert
class Solution1:
    # @param num, a list of integer
    # @return a list of lists of integers
    def permute(self, num):
        if not num:
            return [num]
        
        sub_permutes = self.permute(num[:-1])
        
        permutes = []
        for perm in sub_permutes:
            for i,v in enumerate(perm):
                if v != num[-1]:
                    permutes.append(perm[:i] + [num[-1]] + perm[i:])
            permutes.append(perm + [num[-1]])
        return permutes

# Use Johnson-trotter algorithm

class Solution:
    def permute(self, num):
        pass
