# Generate the kth permutation of johnson-trotter algo in O(n)
# n! = n*(n-1)!
# Therefore, for each perm(n-1), it will be repeated n times in perm(n)
# So k / n is the permutation index of perm(n-1)
# k % n is the position to insert "n" into perm(n-1)

class Solution:
    # @return a string
    def getPermutation(self, n, k):
        return self.recur(n, k-1)
    
    def recur(self, n, k):
        if k == 0:
            return range(1,n+1)

        next_k = k / n
        position = k % n
        perm = self.recur(n-1, next_k)
        if next_k % 2 == 0:
            # even permutation
            perm.insert(n-1-position, n)
            return perm
        else:
            # odd permutation
            perm.insert(position, n)
        return perm

def fact(n):
    res = 1
    for i in xrange(1,n+1):
        res *= i
    return res


def permutations(n):
    for i in xrange(1, fact(n)+1):
        print Solution().getPermutation(n, i)

permutations(4)
