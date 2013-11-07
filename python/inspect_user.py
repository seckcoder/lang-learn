#!/usr/bin/env python
import inspect
a = 3
print inspect.isroutine(a)
def f():
	pass
a = f
print inspect.isroutine(a)
class cls(object):
	pass
a = cls
print inspect.isroutine(a)

