#!/usr/bin/env python
def test_time_module():
    import time
#    print time.time()
    #print time.clock()
    #print time.ctime()
    #print time.gmtime()
    #print time.localtime()
    #t = time.localtime()
    #print time.mktime(t)
    #print time.strftime('%a, %d %b %Y %H:%M:%S +0000', time.gmtime())

def test_timedelta():
    from datetime import timedelta
    year = timedelta(days=365)
test_time_module()
