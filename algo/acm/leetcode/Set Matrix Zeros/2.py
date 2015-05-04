
# O(1) solution

# Use first row and first col as the flag array
class Solution:
    # @param matrix, a list of lists of integers
    # @return nothing (void), do not return anything, MODIFY matrix IN PLACE.
    def setZeroes(self, matrix):
        m = len(matrix)
        if m == 0: return
        
        n = len(matrix[0])
        if n == 0: return

        first_row_zero = False
        first_col_zero = False

        for j in xrange(0, n):
            if matrix[0][j] == 0:
                first_row_zero = True
                break

        for i in xrange(0, m):
            if matrix[i][0] == 0:
                first_col_zero = True
                break
        
        
        for i in xrange(1,m):
            for j in xrange(1, n):
                if matrix[i][j] == 0:
                    # We use zero as the flag number. If equals zero, we should set the row/col as zero.
                    matrix[i][0] = 0
                    matrix[0][j] = 0

        for i in xrange(1, m):
            if matrix[i][0] == 0:
                # we need set the ith row to 0
                for j in xrange(1,n):
                    matrix[i][j] = 0

        for j in xrange(1,n):
            if matrix[0][j] == 0:
                # we need set the jth col to 0
                for i in xrange(1, m):
                    matrix[i][j] = 0

        if first_row_zero:
            for j in xrange(0,n):
                matrix[0][j] = 0

        if first_col_zero:
            for i in xrange(0,m):
                matrix[i][0] = 0
