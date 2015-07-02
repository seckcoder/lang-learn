

# This is a recursive procedure.

# for abc,
# We consider every character which should be the first character

# if it's a, then we get all sub permutations of bc. I expect it return
# "bc" and "cb". Then we insert "a" in the front of every sub permutation
# This will get "abc", "acb"

# if it's b, we get all sub permutations of ac, then we repeat this procedure on and on.


# when s is empty so it will directly return empty list

# O(n! * n) where "n is length of string"
# We need to generate n! number of permutations. To generate each permutation,
# we need O(n). So the total complexity is O(n! * n)

# n is length of the string
def permute(s):

    # just copy it
    res = []
    for i in xrange(len(s)):
        sub_s = s[0:i] + s[i+1:]
        # return all permutation of the sub str
        perms = permute(sub_s)
        for perm in perms:
            # add the char as the first element of each sub permutation
            perm = [s[i]] + perm
            res.append(perm)
    return res


def print_res(s):
    for perm in permute(s):
        print perm

# don't copy this
# shut up




class Solution:

    def permuteUnique(self, num):
        visited = [False] * len(num)
        perms = []
        self.dfs(sorted(num), 0, visited, [], perms)
        return perms

    # visited_count: number of elements visited,
    # visited: flag to record whether an element has been visited
    # Say this: acc is current permutation we are trying to construct. It's an
    # unfinished permutation. 
    # Yes. You are right.
    # perms: is the result
    def dfs(self, s, visited_count, visited, acc, perms):
        n = len(s) 
        # If the visited count is >= n, then we need to break
        # since we have already got an permutation
        if visited_count == n:
            perms.append(list(acc))
            return
        # enumerate through every element.
        for i in xrange(n):
            # we only consider the element that hasn't been visited
            if not visited[i]:
                if i > 0 and s[i] == s[i-1] and not visited[i-1]:
                    # The key point here is removing the duplicates
                    pass
                else:
                    # First, this is the normal dfs procedure.
                    # We first flag an element as visited.
                    # and add the current char to acc.
                    visited[i] = True
                    acc.append(s[i])
                    # Then we continue the recursive procedure for the rest
                    # unvisited chars
                    self.dfs(s, visited_count + 1, visited, acc, perms)
                    # after the dfs, we restore the state to try the rest
                    # chars

                    # This is for back tracking.
                    # At this time, we will remove the eelment we have added.
                    # Note in line 21, we create a copy of acc and add it to the final result.
                    visited[i] = False
                    acc.pop()

                    # O(number of permutations * n).
                    # I don't quite get the question.
                    # Is that right?

print Solution().permuteUnique([1,2,2])



# Just say this.
# 1. You know, the input s is sorted during the preprocessing step. 
# 2. The key problem with the duplicates is:
#   for same chars, we are likely to add the element twice.

# Example:
#  aac -> I will tag the two as as a1 and a2.
#  First suppose we have added a1, then we will add a2 to the permutation,.
# This will generate aac
# For the second time, then we will add a2 first, then we will add a1 and c.
# This create a duplicate. 
# We need to avoid the case.

# My solution is:
#   After the s is sorted, we compare with the currrent character in consideration
# with the previous charater. 
# If the previous character is the same as the current one. If they are equal,
# and the previous has n't been added, then we will surely not add the current one,
# since it will create duplicates.
#


