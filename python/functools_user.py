#!/usr/bin/env python
#-*- coding=utf-8 -*-
#
# Copyright 2013 Jike Inc. All Rights Reserved.
# Author: liwei@jike.com

"""
Provides demos for function in functools
"""
import functools


def demo_update_wrapper():
    def decorator(f):
        def wrapper(*args, **kwargs):
            '''wrapper func'''
            print 'Calling wrapper'
            return f(*args, **kwargs)
        return wrapper

    def example():
        '''Demo for update_wrapper'''
        print "Called example function"

    example_wrapper = decorator(example)
    # NOTE(by seckcoder) : what update_wrapper does here is to overwrite the __name__,
    # __module__, __doc__ attribute of wrapper(ie, example_wrapper) with wrapped's(ie example)
    # and update wrapper(ie, example_wrapper)'s __dict__ with wrapped's(ie, example) __dict__
    # it's just like the wrapper has wrapped in some attributes of wrapped

    functools.update_wrapper(wrapper=example_wrapper,
                             wrapped=example)
    example = example_wrapper
    example()
    print "example_wrapper name:\'{0.__name__}\', doc: \'{0.__doc__}\'".format(example)
def demo_wraps():
    def decorator(f):
        # NOTE(by seckcoder) : what wraps does here is to overwrite the __name__, __module__, 
        # __doc__ attribute of wrapper with f's, and update wrapper's __dict__ with
        # f'__dict__, it's just like wrapper has wrapped in some attributes of f
        @functools.wraps(f)
        def wrapper(*args, **kwargs):
            '''wrapper func'''
            print 'Calling wrapper'
            return f(*args, **kwargs)
        return wrapper

    @decorator
    def example():
        '''Demo for update_wrapper'''
        print "Called example function"
    example()
    print "example_wrapper name:\'{0.__name__}\', doc: \'{0.__doc__}\'".format(example)

    
demo_wraps()
#demo_update_wrapper()
