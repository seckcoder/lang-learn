# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com


import sys
sys.path.append('gen-py')

from thrift import TSerialization
from case.ttypes import TestCase


case = TestCase(id=1, text="hello world")

buf = TSerialization.serialize(case)
base = TestCase()
TSerialization.deserialize(base, buf)
print base.id, base.text
