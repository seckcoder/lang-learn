#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com


# There is a little difference on lexical closures between python and node.js
idx = 1
def foo():
    idx = 0
    def bar():
        #idx += 2   # error
        print idx
    for i in range(0, 10):
        bar()
        print idx

foo()


# compared with node.js
#function foo() {
    #var idx = 3;
    #function bar() {
        #idx += 2;
    #};
    #for (var i = 0; i < 10; i++) {
        #console.log(idx);
        #bar();
    #};
#};
#foo();
