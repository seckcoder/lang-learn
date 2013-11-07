#!/usr/bin/env python
# -*- coding: utf_8 -*-

from collections import defaultdict

class DictDefault(object):
    '''Dict default use case: dict.setdefault, defaultdict;

    defaultdict is useful for settings defaults *before filling the dict*,
    and setdefault is useful for setting defaults *while or after filling the dict*
    Most common use case: Grouping items(in unsorted data, else use itertools.groupby)
    '''
    def __init__(self):
        self.data = {
            'liwei' : 'liwei@jike.com',
            'jiege' : 'jiege@diaosi.com',
        }
    # really verbose way
    def verbose(self):
        d = {}
        for (key, value) in self.data.items():
            if key in d:
                d[key].append( value )
            else:
                d[key] = [value]
        return d
    # easy with setdefault
    def simple(self):
        d = {}
        for (key, value) in self.data.items():
            g = d.setdefault(key, [])
            g.append(value)
        return d
    # even simpler with defaultdict
    def simpler(self):
        d = defaultdict(list)
        for key, value in self.data.items():
            d[key].append(value)
        return d

test = DictDefault()
print test.verbose()
print test.simple()
print test.simpler()
