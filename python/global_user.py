#! /usr/bin/env python
# -*- coding: utf-8 -*-

def foo():
    def foo_sub():
        print g_v
    print g_v
    foo_sub()
def bar():
    def bar_sub():
        print g_v
        g_v = 'bar2'
    print g_v
    bar_sub()
def test():
    def test_sub():
        g_v = 'test1'
    print g_v
    test_sub()
    print g_v

def ubi():
    def test_ubi():
        global g_v
        print g_v
        g_v = 'ubi1'
    print g_v
    test_ubi()
    print g_v
g_v = 'foo'
foo()
g_v = 'bar'
try:
    bar()
except UnboundLocalError as inst:
    print inst
g_v = 'test'
test()
g_v = 'ubi'
ubi()
