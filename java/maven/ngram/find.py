#!/usr/bin/env python

import sys

for line in sys.stdin:
    line = line.strip()
    if line:
        phrase, cnt = line.split('\t')
        if phrase == "life and death":
            print cnt
            break
