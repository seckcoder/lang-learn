#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
import sys
while True:
    line = sys.stdin.readline()
    if not line: break
    line = line.rstrip()
    print 'in_script', line
