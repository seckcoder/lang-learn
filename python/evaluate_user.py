#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
class StudyCase(object):
    def __evaluate__(self):
        print "evaluated"

case = StudyCase()
print case
