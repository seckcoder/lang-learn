#/usr/bin/env python
arr = [5, 2, 1, 3, 4]
print sorted(arr)
class A(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def __str__(self):
        return '%s, %s' % (self.name, self.age)
a = A('liwei', 22)
b = A('old', 33)
c = A('young', 10)
d = A('unknown1', -1)
e = A('unknown2', 2000)
arr = [a, b, c, d, e]
arr.sort(key=lambda obj: obj.age, reverse=True)
for a in arr:
    print a
d = {1:32, 2:22, 3:42, 4:2, 5: 43}
l = sorted(d.keys(), key=lambda k:d[k])
print [d[i] for i in l]
