#!/usr/bin/env python
import os
import sys
print 'file',__file__
print 'relative path', os.path.dirname(__file__)
print 'absolute path', os.path.realpath(__file__)
print 'os path join user', os.path.join('/home/seckcoder', '/home/liwei', 'seckcoder')
print sys.path
sys.path.insert(0, os.path.join(os.path.dirname(__file__),'..'))
print sys.path
