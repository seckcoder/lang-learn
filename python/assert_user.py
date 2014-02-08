#!/usr/bin/env python
a = 1
try:
    assert a != 1, 'a equals 1'
except AssertionError as inst:
    print inst
