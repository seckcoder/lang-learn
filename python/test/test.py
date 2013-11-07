#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

def foo(t):
    print "called"
    return t

res = [tmp for tmp in\
       [foo(t) for t in [1,2,3,4,5]]]
print res
