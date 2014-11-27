#!/usr/bin/env python
import sys
import time

wc = 0
for line in sys.stdin:
    wc += 1
    if wc >= 2:
        time.sleep(1)
        wc = 0
