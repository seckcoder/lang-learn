#! /usr/bin/env python
# -*- coding: utf-8 -*-

class Base1(object):
    def __init__(self):
        print 'base1'
    def foo(self):
        print 'base1 foo'
    def bar1(self):
        print 'base1 bar'

class Base2(object):
    def __init__(self):
        print 'base2'
    def foo(self):
        print 'base2 foo'
    def bar2(self):
        print 'base2 bar'

class Child(Base1, Base2):
    def __init__(self):
        super(Child, self).__init__()
    def foo(self):
        super(Child, self).foo()
        print 'child foo'
    def bar2(self):
        super(Child, self).bar2()
        print 'child bar2'

c= Child()
c.foo()
c.bar2()
c.bar1()

