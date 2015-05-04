# O(m+n) Solution

class Solution:
    # @param matrix, a list of lists of integers
    # @return nothing (void), do not return anything, MODIFY matrix IN PLACE.
    def setZeroes(self, matrix):
        m = len(matrix)
        if m == 0: return
        n = len(matrix[0])
        zero_rows = [0] * m
        zero_cols = [0] * n
        for i in xrange(0, m):
            for j in xrange(0, n):
                if matrix[i][j] == 0:
                    zero_rows[i] = 1
                    zero_cols[j] = 1
        
        for i in xrange(0, m):
            if zero_rows[i] == 1:
                for j in xrange(0, n):
                    matrix[i][j] = 0
        
        for j in xrange(0, n):
            if zero_cols[j] == 1:
                for i in xrange(0, m):
                    matrix[i][j] = 0
