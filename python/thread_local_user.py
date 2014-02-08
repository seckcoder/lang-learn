#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com


# Note that the following code is not an elegant way to pass arguments

# Consider the following code
# A quick and dirty way to pass some data from run to bar
from time import sleep
from random import random
from threading import Thread, local

data = local()

def bar():
    print "I'm called from", data.v

def foo():
    bar()

class T(Thread):
    def run(self):
        sleep(random())
        data.v = self.getName()   # Thread-1 and Thread-2 accordingly
        sleep(1)
        foo()

#
# >> T().start(); T().start()
# I'm called from Thread-2
# I'm called from Thread-1
