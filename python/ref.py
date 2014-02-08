#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

try:
    s = 'abc'
    s[0] = 'b'
except TypeError:
    print 'str is not mutable'
try:
    t = (1, 2, 3)
    t[0] = 2
except TypeError:
    print 'tuple is not mutable'

class A(object):
    def __init__(self):
        self.a = 'a'
    def __str__(self):
        return self.a
def modify(obj):
    obj.a = 'b'
def rebind(obj):
    obj = A()
    obj.a = 'c'
obj = A()
print 'before modify %s' % obj
modify(obj)
print 'after modify %s' % obj
rebind(obj)
print 'after rebind %s' % obj

