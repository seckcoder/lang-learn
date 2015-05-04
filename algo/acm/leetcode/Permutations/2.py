

class Solution:

    def permuteUnique(self, num):
        visited = [False] * len(num)
        perms = []
        self.dfs(sorted(num), 0, visited, [], perms)
        return perms

    def dfs(self, num, visited_count, visited, acc, perms):
        n = len(num)
        if visited_count == n:
            perms.append(list(acc))
            return

        for i in xrange(n):
            if not visited[i]:
                if i > 0 and num[i] == num[i-1] and not visited[i-1]:
                    # Remove the duplicate cases
                    pass
                else:
                    visited[i] = True
                    acc.append(num[i])
                    self.dfs(num, visited_count + 1, visited, acc, perms)
                    visited[i] = False
                    acc.pop()

print Solution().permuteUnique([1,2,2])
