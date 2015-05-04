
# n! = (n-1)! * n. 

# 1 23
# 1 32

# 2 13
# 2 31



def fact(n):
    ans = 1
    for i in xrange(1, n+1):
        ans *= i
    return ans

class Solution:
    # @return a string
    def getPermutation(self, n, k):
        if n == 0: return ""
        fact_n = fact(n-1)
        k -= 1 # start from 0
        elems = range(ord('1'), ord('9')+1)
        acc = ''
        for i in xrange(n-1,0,-1):
            kth = k / fact_n # which element we should get right now
            acc += chr(elems[kth])
            # acc.append(elems[kth])
            elems.remove(elems[kth]) # remove the kth
            k = k % fact_n
            fact_n = fact_n / i
        acc += chr(elems[0])
        return acc


def permutations(n):
    for i in xrange(1,fact(n)+1):
        print Solution().getPermutation(n, i)
    
permutations(3)
