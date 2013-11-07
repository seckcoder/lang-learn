import bisect

a = [10, 2, 8, 20, 25, 7, 3, 19, 10, 10, 2, 7, 6, 5, 82, 3, 49]

a.sort()
print a
print bisect.bisect_left(a, 5)
print bisect.bisect_right(a, 5)
