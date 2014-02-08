#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com


# python的文件读取的seek, read, readline, tell等函数不要与iterator(即next()函数)
# 混用， 否则会出现诡异的结果. 当使用codecs打开文件时，其

import codecs

#with codecs.open('page_test.log', 'r', 'utf-8') as fin:
with open('page_test.log', 'r') as fin:
    for i in range(10):
        print fin.tell(), fin.readline()
    #print fin.tell(), fin.next()
    #print fin.tell(), fin.next()
