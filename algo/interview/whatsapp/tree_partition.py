import math

def perfect_tree_partition(n):
    """find the point to partition n keys for a perfect binary tree"""
    x = 1

    # find a power of 2 <= n//2
    # while x <= n//2:  # this loop could probably be written more elegantly :)
    #     x *= 2
    x = 1 << (n.bit_length() - 1)   # indeed you can

    # // is floor division
    if x//2 - 1 <= (n-x):
        # print x, x//2-1, n-x,"here",
        return x - 1      # case 1
    else:
        # print x, x//2 - 1, n-x, "there",
        return n - x//2   # case 2 == n - (x//2 - 1) - 1


def perfect_tree_partition1(n):
    k = int(math.log((n-1)//2+1, 2))

    rest_elems = n - 2*(2**k-1) -1
    left_num = 2**k-1 + min(rest_elems, 2**k)
    return left_num


for i in range(1, 1000000):
    assert perfect_tree_partition(i) == perfect_tree_partition1(i)
