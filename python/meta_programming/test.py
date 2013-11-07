#!/usr/bin/python

class _MetaPacket(object):
    def __new__(cls, *args, **kw):
        return object.__new__(cls)

m = _MetaPacket()
