#!/usr/bin/env python

import random

with open("data/external_sorting.dat", "w") as fout:
    for i in range(0, 4*2):
        fout.write(str(random.randint(1,10000)))
        fout.write(" ")
