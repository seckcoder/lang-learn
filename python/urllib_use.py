#! /usr/bin/env python
#coding=utf8
import urllib
d = {'hl':'en', 'safe':'off'}
print urllib.quote('http://www.google.com/search?%s' % urllib.urlencode(d))
