#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import re
from urlparse import urlparse

def parse1():
    p = re.compile(r"/(?P<uid>\d+)/(?P<mid>\w+)")
    o = urlparse("http://weibo.com/2827699110/yz62AlEjF")
    m = p.search(o.path)
    print m.group('uid')
    print m.group('mid')
def parse2():
    exc_type_str = "<type 'exceptions.IndexError'>"
parse1()
