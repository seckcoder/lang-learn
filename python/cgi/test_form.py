#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import cgi

form = cgi.FieldStorage()
val1 = form.getvalue('comments')
print """Content-type: text/html

The form input is below...<br/>"""
print val1
