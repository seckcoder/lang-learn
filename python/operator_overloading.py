#!/usr/bin/env python
# -*- coding: utf_8 -*-
class Prod:
	def __init__(self, value):
		self.value = value
	def __call__(self, other):
		return self.value * other
	def __getitem__(self, other):
		return self.value * other
	def __getattr__(self, attr):
		if attr == 'age':
			return 40
		else:
			raise AttributeError, 'no attr:'+attr+' exist'
class ProdSub(Prod):
	def __getitem__(self, index):
		return self.data[index]
x = Prod(2)
print '__call__:',x(3)
print '__getitem__:',x[5]
print '__getitem__ list attribute:'
x_sub = ProdSub(2)
x_sub.data='spam'
print ('p' in x_sub)
print [c for c in x_sub]
map(None, x_sub)
(a,b,c,d) = x_sub
print (a,b,c,d)
print ''.join(x_sub)
print list(x_sub)
print '__getattr__:', x.age
try:
	print '__getattr__:', x.name
except Exception, reason:
	print reason

class cls_nostr_norepr(object):
	def __init__(self):
		super(cls_nostr_norepr, self).__init__()
class cls_norepr(cls_nostr_norepr):
	'''
	when there is no repr, repr(object) will not call str(object)
	'''
	def __str__(self):
		return '[cls_nostr]'
class cls_nostr(cls_nostr_norepr):
	'''
	when there is no str, str(object) will call repr(object)
	'''
	def __repr__(self):
		return '[cls_norepr]'
class cls_both(cls_nostr, cls_norepr):
	'''
	when there is both str and repr, print calls str
	'''
	def __init__(self):
		super(cls_both, self).__init__()
def strform_test(x):
	print 'test class:',x.__class__.__name__
	print '[1:]',x
	print '[2:]',str(x)
	print '[3:]',repr(x)
x = cls_nostr_norepr()
strform_test(x)
x = cls_nostr()
strform_test(x)
x = cls_norepr()
strform_test(x)
x = cls_both()
strform_test(x)

class super1:
	def hello(self):
		self.data1 = 'super1'
class super2:
	def hello(self):
		self.data1 = 'super2'
class sub(super1, super2):
	def hola(self):
		self.data2 = 'sub'
X = sub()
print 'sub base classes: ',X.__class__.__bases__
X.hola()
print 'X dict:',X.__dict__
print 'X class dict:',X.__class__.__dict__
sub.data3 = 'python'
print 'X dict:',X.__dict__
print 'X class dict:',X.__class__.__dict__
super1.data1 = 'data1---super'
print X.data1


print 'Use __str__ with unicode'
class Bottle(object):
	'''
	Reference:http://stackoverflow.com/questions/8222270/python-how-to-force-a-print-to-use-unicode-instead-of-str-or-otherwi
	'''
	def __init__(self, s):
		self.s = s
	def __str__(self, encoding='utf-8'):
		return self.__unicode__().encode(encoding)
	def __unicode__(self):
		str = u'%s' % self.s
		return str
b = Bottle(u'哈哈')
print u'%s' % b
try:
	print 'Not use this way'
	b = Bottle('哈哈')
	print u'%s' %b
except Exception, reason:
	print 'Error:', reason
