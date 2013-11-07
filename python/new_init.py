#!/usr/bin/env python
class base(object):
    def __new__(*args, **kw):
        print "base new"
        return object.__new__(*args, **kw)
    def __init__(*args, **kw):
        print "base init"
class A(base):
    def __init__(*args, **kw):
        print "A init"
class B(base):
    def __new__(*args, **kw):
        print "B new"
        return object.__new__(*args, **kw)
    def __init__(*args, **kw):
        print "B init"
        return object.__init__(*args, **kw)
class C(base):
    def __new__(*args, **kw):
        print "C new"
    def __init__(*args, **kw): # this is not called
        print "C init" 
class D():
    def __init__(*args, **kw):
        print "D init"
    
class E(object):
    def __new__(cls, *args, **kw):
        print cls
        print E
        print args
        new_instance = object.__new__(cls)
        return new_instance
    def __init__(self, a, b):
        print a,b

def test_new_init():
    """ __init__ is called only
        when __new__ return a instance correctly"""
    a = base()
    print a
    a = A()
    print a
    a = B()
    print a
    a = C()
    print a
    a = D()
    print a
def test_new():
    a = E('a','b')
    if isinstance(a, E):
        print "is instance"
    if issubclass(E, object):
        print "is subclass"
    c = object.__new__(base)
    print c

if __name__ == '__main__':
    #test_new_init()
    test_new()

