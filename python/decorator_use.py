#!/usr/bin/env python

class Multi_e1:
	def imeth(self, x):
		print self,x
	def smeth(x):
		print x
	def cmeth(cls, x):
		print cls,x
	smeth = staticmethod(smeth)
	cmeth = classmethod(cmeth)
e1 = Multi_e1()
e1.imeth(1)
Multi_e1.smeth(1)
Multi_e1.cmeth(1)

class Multi_e2:
	def imeth(self,x):
		print self,x
	@staticmethod
	def smeth(x):
		print x
	@classmethod
	def cmeth(cls, x):
		print cls,x
e2 = Multi_e2()
e2.imeth(2)
Multi_e2.smeth(2)
Multi_e2.cmeth(2)

class tracer:
	def __init__(self, func):
		self.calls = 0
		self.func = func
	def __call__(self, *args):
		self.calls += 1
		print 'call %s to %s' % (self.calls, self.func.__name__)
		self.func(*args)
@tracer
def spam1(a,b,c):
	print a,b,c,'spam1'
def spam2(a,b,c):
	print a,b,c,'spam2'
spam2 = tracer(spam2)
spam1(1,2,3)
spam2(1,2,3)
