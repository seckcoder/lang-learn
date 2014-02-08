#!/usr/bin/env python
#-*- coding=utf-8 -*-
import logging

def config_log():
    numeric_level = getattr(logging, 'INFO', None)
    if not isinstance(numeric_level, int):
        raise ValueError('Invalid log level')
    logging.basicConfig(filename='example.log', filemode='w', level=numeric_level,format='%(asctime)s %(message)s')

class MyException(Exception):
    pass

def simple_test():
    logging.debug('debug---log')
    logging.info('info---log')
    logging.warning('warning---log')
    logging.error('error---log')
    logging.critical('critical---log')
    try:
        raise MyException("this is an exception")
    except:
        logging.exception("an exception happened")
    print "see example.log for log messages"
if __name__ == '__main__':
    config_log()
    simple_test()
