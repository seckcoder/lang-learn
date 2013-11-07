#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
import random
import time
import threadpool
from threadpool import *
import traceback
import sys
import Queue
def print_result(request, result):
    print "**** Result from request #%s: %r" % (request.requestID, result)
def handle_exception(request, exc_info):
    if not isinstance(exc_info, tuple):
        # Something is seriously wrong...
        print request
        print exc_info
        raise SystemExit
    print "**** Exception occured in request #%s: %s" % \
      (request.requestID, exc_info)
    #traceback.print_exception(*exc_info)
    for var in traceback.format_exception(*exc_info):
        print var

class A(object):
    def foo(self, foo_args=None):
        print '*****************'
a = A()


data = [random.randint(1,10) for i in range(20)]
requests = makeRequests(a.foo, [None], print_result, handle_exception)

main = ThreadPool(3)
for req in requests:
    main.putRequest(req)
i = 0
#time.sleep(0.01)
while True:
    try:
        main.poll()
    except threadpool.NoResultsPending:
        break
if main.dismissedWorkers:
    print "Joining all dismissed worker threads..."
    main.joinAllDismissedWorkers()
print 'Finally finished'
