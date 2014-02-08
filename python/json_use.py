#!/usr/bin/env python
# -*- coding: utf_8 -*-
import json
from StringIO import StringIO 
io = StringIO()
json.dump(['streaming api'], io)
print io.getvalue()
def as_complex(dct):
    if '__complex__' in dct:
        return complex(dct['real'], dct['imag'])
    return dct
json_data = '{"__complex__":true, "real":1, "imag":2}'
data = json.loads(json_data, object_hook = as_complex)
print data
