#!/usr/bin/env python
class A(object):
	def __init__(self):
		print "A init"
class B(object):
	def __init__(self):
		print "B init"
class C(B,A):
	def __init__(self):
		"""super(type,[object-or-type2])
		   isinstance(object, type)  or
		   issubclass(type2, type)
		"""
		print "C init"
		super(C, self).__init__()

c = C()


print 'illustrate the func call between Parent and child'

class Parent(object):
    def foo(self):
        print 'Parent foo'
    def bar(self):
        self.foo()
    def bar2(self):
        self.foo()
class Child(Parent):
    def foo(self):
        print 'Child foo'
    def bar(self):
        super(Child, self).bar()

c = Child()
c.bar() # Child foo called
c.bar2() # Child foo called
