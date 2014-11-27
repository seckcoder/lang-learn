#!/usr/bin/env python
import sys
import traceback

try:
    5 / 0
except ZeroDivisionError as e:
    ex = traceback.format_exception(*sys.exc_info())
    print ''.join(ex)
