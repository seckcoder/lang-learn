#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

"""Any identifier of the form __spam (at least two leading underscores, at most one trailing underscore) is textually replaced with _classname__spam, where classname is the current class name with leading underscore(s) stripped. This mangling is done without regard to the syntactic position of the identifier, so it can be used to define class-private instance and class variables, methods, variables stored in globals, and even variables stored in instances. private to this class on instances of other classes."""

def how_to():
    class C1(object):
        def meth1_a(self):
            self.__X = 88
        def meth1_b(self):
            print self.__X
    c = C1()
    c.meth1_a()
    try:
        print c.__X
    except AttributeError as inst:
        print inst
        print c._C1__X

def why():
    class C1(object):
        def meth1_a(self):
            self.x = 1
            self.__x = 10
        def meth1_b(self):
            print self.x
            print self.__x
    class C2(object):
        def meth2_a(self):
            self.x = 2
            self.__x = 20
        def meth2_b(self):
            print self.x
            print self.__x
    class C3(C1, C2):
        pass
    c = C3()
    c.meth1_a()
    c.meth2_a()
    c.meth1_b()
    c.meth2_b()
    print '-----------'
    c.meth2_a()
    c.meth1_a()
    c.meth1_b()
    c.meth2_b()

why()
