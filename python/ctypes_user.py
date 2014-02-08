#!/usr/bin/env python
from ctypes import *
class Point(Structure):
    _fields_ = ("x", c_int), ("y", c_int)

class Rect(Structure):
    _fields_ = ("a", Point), ("b", Point)
p1=  Point(1, 2)
p2 = Point(3, 4)
rc = Rect(p1, p2)
print rc.a.x, rc.a.y, rc.b.x, rc.b.y
#rc.a, rc.b = rc.b, rc.a
#print rc.a.x, rc.a.y, rc.b.x, rc.b.y
temp0, temp1 = rc.b, rc.a
print 'rc.a,', rc.a, rc.a.x, rc.a.y
print 'rc.b,', rc.b, rc.b.x, rc.b.y
print 'temp0,', temp0, temp0.x, temp0.y
print 'temp1,', temp1, temp1.x, temp1.y
#Keep in mind that retrieving sub-objects from Structure, Unions, and Arrays doesn’t copy the sub-object, instead it retrieves a wrapper object accessing the root-object’s underlying buffer.
rc.a = temp0 #actually copies rc.b's content to rc.a
print 'rc.a,',rc.a, rc.a.x, rc.a.y
print 'temp1,', temp1, temp1.x, temp1.y
rc.b = temp1
print 'rc.b,',rc.b,rc.b.x,rc.b.y
