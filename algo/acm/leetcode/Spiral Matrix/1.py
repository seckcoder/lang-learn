
# Recursive solution.
# Get rid of an outer loop every time

class Solution1:
    # @param matrix, a list of lists of integers
    # @return a list of integers
    def spiralOrder(self, matrix):
        m = len(matrix)
        if m == 0: return []
        n = len(matrix[0])
        if n == 0: return []
        
        acc = []
        
        self.spiralRecur(matrix, (0,0), (m,n), acc)
        return acc
        
    def spiralRecur(self, matrix, start, range, acc):
        (x,y) = start
        (m,n) = range

        if m <= 0 or n <= 0: return

        if m == 1:
            i = x
            for j in xrange(y,y+n):
                acc.append(matrix[i][j])
            return
        
        elif n == 1:
            j = y
            for i in xrange(x,x+m):
                acc.append(matrix[i][j])
            return
            

        # Note: We need to update i,j accordingly.
        i = x
        # right
        for j in xrange(y, y+n-1):
            acc.append(matrix[i][j])
        
        j = y+n-1
        # down
        for i in xrange(x, x+m-1):
            acc.append(matrix[i][j])
        
        i = x+m-1
        # left
        
        for j in xrange(y+n-1, y, -1):
            acc.append(matrix[i][j])
        
        j = y
        
        for i in xrange(x+m-1, x, -1):
            acc.append(matrix[i][j])
        
        self.spiralRecur(matrix, (x+1,y+1), (m-2,n-2), acc)

def generateSpiralFrameCoords(p, r):
    px,py = p
    rx,ry = r
    
    if px == rx:
        # Only One line (Horizontal)
        for y in xrange(py,ry+1):
            yield (px,y)
    elif py == ry:
        # Only One line (vertical)
        for x in xrange(px,rx+1):
            yield (x,py)
    else:
# Right: Fix x

        # generateRight(py, ry, px, 1)

        for y in xrange(py, ry):
            yield (px, y)

# Down : Fix y


        # generateDown(px, rx, ry, 1)

        for x in xrange(px, rx):
            yield (x, ry)

# Left: Fix x

        # generateLeft(ry, py, rx, -1)
        
        for y in xrange(ry, py,-1):
            yield (rx, y)

# Up : Fix y

        # generateUp(rx, px, py, -1)

        for x in xrange(rx, px, -1):
            yield (x, py)


# m x n matrix
def generateSpiralCoords(m,n):
    px,py = (0,0)
    rx,ry = (m-1,n-1)

    while (px <= rx) and (py <= ry):
        for coord in generateSpiralFrameCoords((px,py),(rx,ry)):
            yield coord
        px += 1
        py += 1
        rx -= 1
        ry -= 1

class Solution:
    def spiralOrder(self, matrix):
        m = len(matrix)
        if m == 0: return []
        n = len(matrix[0])
        if n == 0: return []

        
        return [matrix[i][j] for i,j in generateSpiralCoords(m,n)]

print Solution().spiralOrder([[6,9,7]])
