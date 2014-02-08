#!/usr/bin/env python
import sys
def min_user():
    print 'min---start'
    a=[3,1,2]
    b=[0, -2]
    print min(a, -1, *b)
    a=[{'num':1}, {'num':2}, {'num':3}]
    print min(a, key=lambda item: item['num'])
    print 'min---end'
def dir_user():
    print 'dir----- start'
    print dir()
    a = 3
    print dir()
    del a
    print dir()
    print dir()
    print dir(sys)
    print 'dir---- finish'
def __file__user():
    print 'get relative file path(contains file name)', __file__
def property_user():
    class C(object):
        def __init__(self):
            pass
        def make_property(attr):
            def set_attr(self, value):
                setattr(self, 'transform_'+attr, value)
            def get_attr(self):
                return getattr(self, "transform_"+attr)
            return property(
                get_attr,
                set_attr
                )
        x = make_property('x')
    c = C()
    c.x = 'hello'
    print c.x
    print dir(c)
    print c.transform_x
property_user()

