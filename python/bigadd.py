import itertools
def bigadd(a, b):
    z = [x+y for x,y in itertools.izip_longest(reversed(a),reversed(b),fillvalue=0)]
    res = [x+y for x,y in itertools.izip_longest([i%10 for i in z],[0] + [i/10 for i in z],fillvalue=0)]
    [x for x in itertools.dropwhile(lambda x: x == 0, reversed(res))]

print bigadd([1,2,3], [4,5,6,8])
