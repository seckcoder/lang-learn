#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import sys
import codecs
out = codecs.open('result', 'w', 'utf-8')
f_in = codecs.open('category', 'r', 'utf-8')
for line in f_in:
    line_list = line.split('\n')
    for l in line_list:
        if l:
            out.write(l)
            out.write('\n')
f_in.close()
out.close()

