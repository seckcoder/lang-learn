# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

s1 = set([1, 2, 3])
s2 = set([2, 3, 4])

print "hello world"


print 's1: %s' % s1
print 's2: %s' % s2
print 'operation on s1 and s2'
print '\tUnion: %s' % (s1 | s2)
tmp = s1.copy()
tmp |= s2
print '\tUnion update %s' % tmp
tmp = s1.copy()
tmp &= s2
print '\tintersection_update %s' % tmp
tmp = s1.copy()
tmp -= s2
print '\tdifference_update %s' % tmp
tmp = s1.copy()
tmp ^= s2
print '\tsymmetric_difference_update %s' % tmp

def test():
  print "hello world"

test()