#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2012 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
from urlparse import urlparse
url = 'http://www.google.com/search?hl=en&safe=off&q=atomized&btnG=Search'
def get_query_value(url, query_key):
    '''Return a query value of url according to query_key'''
    params = dict([part.split('=') for part in urlparse(url)[4].split('&')])
    print params
    return params[query_key]
print get_query_value(url, 'hl')
