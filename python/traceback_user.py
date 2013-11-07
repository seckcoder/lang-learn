#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
import sys, traceback
def lumberjack():
    bright_side_of_death()
def bright_side_of_death():
    #return tuple()[0]
    raise RuntimeError('运行时错误')
try:
    lumberjack()
except RuntimeError:
    exc_type, exc_value, exc_traceback = sys.exc_info()
    exc_type_str = '%s' % exc_type
    print exc_type_str
    print exc_value
    print '------------------------------------------------------------------------------'
    traceback.print_tb(exc_traceback)
    tb_info = traceback.format_tb(exc_traceback)
    print '------------------------------------------------------------------------------'
    print ''.join(tb_info)
