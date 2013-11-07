#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
import random

class Die(object):
    def __init__(self, sides=6):
        self.sides = sides
    def __get__(self, instance, owner):
        print instance.__dict__
        print owner.__dict__
        return int(random.random() * self.sides) + 1


class Game(object):
    d6 = Die()
    d10 = Die(sides=10)
    def __init__(self):
        self.d20 = Die(sides=20)

def demo_game():
    g = Game()

    print g.d6
    print g.d10
    print "**"
    print g.d20

def retrieve():
    v = None
    for i in xrange(1000):
        v = random.randint(1, 1000)
    return v
class cached_property(object):
    def __init__(self, fget=None, fset=None, fdel=None):
        self.__get = fget
        self.__name__ = fget.__name__
        self.__set = fset
        self.__del = fdel
    def __get__(self, instance, owner):
        if instance is None:
            return self
        try:
            return instance.__dict__[self.__name__]
        except KeyError:
            value = instance.__dict__[self.__name__] = self.__get(instance)
            return value
    def __set__(self, instance, value):
        if instance is None:
            return self

        if self.__set is not None:
            value = self.__set(instance, value)
        instance.__dict__[self.__name__] = value
    def __delete__(self, instance):
        if instance is None:
            return self
        try:
            value = instance.__dict__.pop(self.__name__)
        except KeyError:
            pass
        else:
            if self.__del is not None:
                self.__del(instance, value)
    def setter(self, fset):
        return self.__class__(self.__get, fset, self.__del)
    def deleter(self, fdel):
        return self.__class__(self.__get, self.__set, fdel)

class Demo(object):
    @cached_property
    def limit(self):
        return retrieve()
    @limit.setter
    def set_limit(self, value):
        pass
    @limit.deleter
    def del_limit(self, value):
        pass

def demo_cached():
    d = Demo()
    print d.limit, d.limit, d.limit, d.limit
    d.limit = 2
    print d.limit, d.limit, d.limit, d.limit
    del d.limit
    print d.limit, d.limit, d.limit, d.limit

demo_cached()
