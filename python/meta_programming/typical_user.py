#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com
class _MetaPacket(type):
    def __new__(cls, clsname, clsbases, clsdict):
        """
        Called to create a new instance of class cls. The remaining
        arguments(clsname, clsbases, clsdict) are those passed to
        the object constructor expression (ie, the call to the class)
        If __new__() returns an instance of cls, then the new instance’s __init__()
        method will be invoked like __init__(self[, ...]),
        where self is the new instance and the remaining arguments are the same as were passed to __new__().
        If __new__() does not return an instance of cls, then the new instance’s __init__() method will not be invoked.
        """
        t = type.__new__(cls, clsname, clsbases, clsdict)

        st = getattr(t, '__hdr__', None)
        if st is not None:
            """The proper use of __slots__ is to save space in objects. Instead of having a dynamic dict that allows adding attributes to objects at anytime, there is a static structure which does not allow additions after creation. This saves the overhead of one dict for every object that uses slots. While this is sometimes a useful optimization, it would be completely unnecessary if the Python interpreter was dynamic enough so that it would only require the dict when there actually were additions to the object.  Unfortunately there is a side effect to slots. They change the behavior of the objects that have slots in a way that can be abused by control freaks and static typing weenies. This is bad, because the control freaks should be abusing the metaclasses and the static typing weenies should be abusing decorators, since in Python, there should be only one obvious way of doing something. Making CPython smart enough to handle saving space without __slots__ is a major undertaking, which is probably why it is not on the list of changes for P3k (yet)."""
            clsdict['__slots__'] = [ x[0] for x in st ]
            t = type.__new__(cls, clsname, clsbases, clsdict)
            t.__hdr_fields__ = [ x[0] for x in st ]
            t.__hdr_fmt__ = getattr(t, '__byte_order__', '>') + \
                    ''.join([ x[1] for x in st] )
            t.__hdr_defualts__ = dict(zip(
                t.__hdr_fields__, [ x[2] for x in st ]))
        return t
    def __init__(self, *args, **kw):
        print '_MetaPacket init'
        print args
        self.meta_attr = 10

class Packet(object):
    __metaclass__ = _MetaPacket

class StudyCase(object):
    pass
class Ethernet(Packet, StudyCase):
    __hdr__ = (
        ('dst', '6s', ''),
        ('src', '6s', ''),
        ('type', 'H', 10)
    )

e = Ethernet()
for attr in dir(e):
    if attr not in dir(object):
        print attr
#print '------------------------------------------------------------------------'

#o = _MetaPacket('Othernet', (object,), {})
#for attr in dir(e):
    #if attr not in dir(object):
        #print attr
