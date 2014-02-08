#! /usr/bin/env python
def __init__(self):
	self.message = 'hello world'
def say_hello(self):
	print self.message
def __str__(self):
    return 'hello world'
attrs = {'__init__':__init__, 'say_hello':say_hello, '__str__':__str__}
bases = (object,)
Hello = type('Hello', bases, attrs)
print 'Hello:', Hello
h = Hello()
h.say_hello()
b = h
print 'id of b and h'
print '\t', id(h)
print '\t', id(b)

print '__metaclass__'
class meta_A(type):
    def __str__(cls):
        return 'hello world'
class A(object):
    __metaclass__ = meta_A
class NonTypeA(object):
        pass
print 'A:', A
print 'type of A:', type(A)
print 'type of NonTypeA:', type(NonTypeA)
print 'str of A:', str(A)
B = meta_A('NewA', bases, attrs)
print 'B:', B
print 'str of B:', str(B)
a = A()
print 'instance of A:', a
b = B()
print 'instance of B:', b
