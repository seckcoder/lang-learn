

# copy with the help of another matrix
class Solution1:
    # @param matrix, a list of lists of integers
    # @return nothing (void), do not return anything, modify matrix in-place instead.
    def rotate(self, matrix):
        n = len(matrix)
        if n == 0:
            return []
        
        new_mat = []
        for i in range(n):
            new_mat.append([0] * n)
        
        for i in xrange(n):
            for j in xrange(n):
                col = n-1-i
                row = j
                new_mat[row][col] = matrix[i][j]
        
        for i in xrange(n):
            for j in xrange(n):
                matrix[i][j] = new_mat[i][j]



# in-place copy
class Solution2:
    def rotate(self, matrix):
        n = len(matrix)
        if n == 0:
            return []


        # rotate by 90 degrees(clockwise)
        def rotateCoord(x,y):
            return y,n-1-x

        # copy the outer frame
        # assert this is a square of size >= 2
        def copyOuterFrame(p,r):
            px,py = p
            rx,ry = r
            
            for y1 in xrange(py,ry):
                x1 = px
                x2,y2 = rotateCoord(x1,y1)
                x3,y3 = rotateCoord(x2,y2)
                x4,y4 = rotateCoord(x3,y3)
                tmp4 = matrix[x4][y4]
                matrix[x4][y4] = matrix[x3][y3]
                matrix[x3][y3] = matrix[x2][y2]
                matrix[x2][y2] = matrix[x1][y1]
                matrix[x1][y1] = tmp4
    
        px,py = 0,0
        rx,ry = n-1,n-1

        while px < rx and py < ry:
            copyOuterFrame((px,py), (rx,ry))
            px += 1
            py += 1
            rx -= 1
            ry -= 1

# The fancy method
# First flip by diagonal direction
# Second flip by horizontal direction

class Solution:
    def rotate(self, matrix):
        n = len(matrix)
        if n == 0:
            return []
        
        for i in xrange(n-1):
            for j in xrange(n-i-1):
                matrix[i][j],matrix[n-1-j][n-1-i] = matrix[n-1-j][n-1-i],matrix[i][j]

        for i in xrange(n/2):
            for j in xrange(n):
                matrix[i][j],matrix[n-1-i][j] = matrix[n-1-i][j],matrix[i][j]
