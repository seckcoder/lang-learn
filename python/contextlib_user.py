#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import urllib
from contextlib import contextmanager, closing

@contextmanager
def tag(name):
    print "<%s> " % name  # this is equivalent to the __enter__ of with as context manager
    try:
        yield "Hello world"  # NOTE(by seckcoder) : After yield, the codes in the with block will start to execute. The exceptions raised in the with block will berreraised here, so we can catch the exception and do something we want(such as cleanup, etc)
    except Exception, e:
        print "Exception %s happened" % e       # this is equivalent to the __exit__ of with as context manager
    print "<%s> " % name

with tag("h1") as s:
    print s
    raise Exception("Fuck!!!!")


# NOTE(by seckcoder) : closing is equivalent to
"""
@contextmanager
def closing(thing):
    try:
        yield thing
    finally:
        thing.close()
"""
with closing(urllib.urlopen("http://www.baidu.com")) as page:
    for line in page:
        print line
