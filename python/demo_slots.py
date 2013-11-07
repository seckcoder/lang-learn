#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

def thesetattr(x, n, v):
    setattr(x._get_current_object(), n, v)
def thestr(x):
    return str(x._get_current_object())
class Study(object):
    """By default, instances of both old and new-style classes have a dictionary for attribute storage. This wastes space for objects having very few instance variables. The space consumption can become acute when creating large numbers of instances.
    The default can be overridden by defining __slots__ in a new-style class definition. The __slots__ declaration takes a sequence of instance variables and reserves just enough space in each instance to hold a value for each variable. Space is saved because __dict__ is not created for each instance.
    __slots__
        This class variable can be assigned a string, iterable, or sequence of strings with variable names used by instances. If defined in a new-style class, __slots__ reserves space for the declared variables and prevents the automatic creation of __dict__ and __weakref__ for each instance.

        Without a __dict__ variable, instances cannot be assigned new variables not listed in the __slots__ definition. Attempts to assign to an unlisted variable name raises AttributeError. If dynamic assignment of new variables is desired, then add '__dict__' to the sequence of strings in the __slots__ declaration.
    """
    __slots__ = ('__local', '__args',)
    def __init__(self, local, args):
        """
        Note the way we define and fetch slots(slots are implemented at the class level)
        """
        object.__setattr__(self, '_Study__local', local)
        object.__setattr__(self, '_Study__args', args)
    def _get_current_object(self):
        loc = object.__getattribute__(self, '_Study__local')
        return loc(*self.__args)
    __setattr__ = thesetattr
    __str__ = thestr


def bar():
    print "bar"
def foo(a):
    print "foo called with", a
    return bar
case = Study(foo, (123,))
print case
