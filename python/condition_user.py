#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

from threading import Condition
from threading import Lock
from threading import Thread
import time
from Queue import Queue

queue = Queue()
mutex = Lock()
cv = Condition(mutex)

def complex():
    def put_item(item):
        cv.acquire()
        queue.put(item)
        print "we already put an item, but we block for 2 seconds"
        time.sleep(2)
        print "now, notify..."
        cv.notify()
        cv.release()


    def get_item():
        cv.acquire()
        while queue.empty():
            cv.wait()

        print queue.get()
        cv.release()

    t1 = Thread(target=get_item)
    t1.start()
    t2 = Thread(target=put_item, args=(3,)) 
    t2.start()

def simple():
    def put_item(item):
        with cv:
            queue.put(item)
            print "we already put an item, but we block for 2 seconds"
            time.sleep(2)
            print "now, notify..."
            cv.notify()
    
    def get_item():
        with cv:
            while queue.empty():
                cv.wait()
            print queue.get()

    t1 = Thread(target=get_item)
    t1.start()
    t2 = Thread(target=put_item, args=(4,)) 
    t2.start()

simple()
