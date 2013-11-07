#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
from StringIO import StringIO

file = '/etc/passwd'
lines = open(file, 'r').readlines()
text = open(file, 'r').read()
f = StringIO()
for line in lines[:-2]:
    f.writelines(line)
f.writelines(lines[-2:])
f.seek(len(lines[0]))
f.write(lines[1])
f.seek(0)
print 'First line = ', f.readline()
print 'Position = ', f.tell()
line = f.readline()
print 'Second line = ', line
f.seek(-len(line), 1)
line2 = f.read(len(line))
print line2
