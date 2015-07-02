


def cubeRoot(n):
    for x in xrange(1, n):
        if x*x*x > n:
            return x


print cubeRoot(100000)

max_c = 830584
