import gevent
from gevent import Greenlet
import time

def foo():
    print 'foo'
    print 'foo again'
    return "haha"

def bar():
    print 'bar'
    gevent.sleep(0)
    print 'bar again'

g = Greenlet(foo)

class Study(object):
    def __call__(self, args):
        print "callback"
case = Study()
g.link(case)
g.start()
g.join()
