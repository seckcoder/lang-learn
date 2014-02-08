#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

from mock import MagicMock
class ProductionClass(object):
    def method(self):
        self.something(1,2)

    def something(self, a, b):
        print a, b

    def sync_todb(self):
        print 'sync to database'


def log_args(*args, **kwargs):
    if not args and not kwargs:
        print 'no args'
    else:
        for arg in args:
            print arg
        for key, value in kwargs.items():
            print '%s:%s' % (key, value)


def mock_user():
    prod = ProductionClass()
    ProductionClass.sync_todb = MagicMock(
        name='sync_todb',
        side_effect=log_args)
    prod.sync_todb()
    print prod.sync_todb.call_args
