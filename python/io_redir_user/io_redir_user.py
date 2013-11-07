#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import sys
from StringIO import StringIO

buff = StringIO()
temp = sys.stdout
sys.stdout = buff  # redirect stdout to buff
print 'hahaha'
sys.stdout = temp
print buff.getvalue()
buff.seek(0)
temp = sys.stdin
sys.stdin = buff  # redirect stdin to buff
var = sys.stdin.readline()
sys.stdin = temp
print var
