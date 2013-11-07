#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
import heapq
import random
h = []
for i in xrange(10):
    heapq.heappush(h, random.randint(1, 10000))
while h:
    print heapq.heappop(h)
h=[]
for i in xrange(10):
    h.append(random.randint(1, 10000))
print 'list :', h
#print '2 largest', heapq.nlargest(2, h)
heapq.heapify(h)
print h

