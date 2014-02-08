#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

class People(object):
    def __init__(self, name, age):
        self.name = name
        self.age = age

p1 = People(name='liwei', age=1)
p2 = People(name='seckcoder', age=2)
p3 = People(name='wangdapeng', age=3)

plist = [p1, p2, p3]

print max(plist, key=lambda p: p.age).age
