#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

import random
from collections import defaultdict

ntimes = 1000
#ntimes = 1

decision = {
    "1": "Graphics(Goal->read popular game engine source code, write a game engine/rendering engine of myself)",
    "2": "Operating system(Goal->read linux kernel source code, linux from scratch)",
    "3": "Big Data, machine learning, nlp(Techniques to mining big data, big data processing, etc; Goal->implemented various big data algorithm of the book mining of massive datasets, pass the stanford machinelearning and nlp courses, read related papers, implement various machine learning algorithm)",
    "4": "erlang; Concurrent programming and distributed programming(Goal->use erlang, read erlang source code)",
    "5": "Algorithm(algorithm complexity analysis, algorithm implementation, various algorithm; Goal->read introduction to algorithm, concrete mathematics, the art of computer programming, implemented the algorithm, hack topcoder)",
    "6": "Network programming(http protocol, tcp/ip, network protocol, etc; Goal->read tcp/ip详解, implemented tcp/ip; read http protocol and the corresponding code in linux kernel, try to implement http, tcp/ip)",
    "7": "Functional programming(various programming language, compiler related; Goal->try to be familiar with Closure,erlang and haskell, read functional programming related books, implement a compiler for functional programming)"
}

results = defaultdict(lambda:0)

for i in xrange(ntimes):
    tmp = random.randint(1,7)
    results[tmp] += 1


res=sorted(results.iteritems(), key=lambda item: item[1])

for t in res:
    print decision[str(t[0])]
