
# A general generator to generate spiral coordinates.


# A dead simple frame coord generator. No need to
# coord calculation.
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


for coord in generateSpiralCoords(3,3):
    print coord
