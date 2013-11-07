import gevent
from gevent.pool import Pool
import random
from functools import partial
def on_exception(fun, greenlet):
    print "on_exception"
    fun()

def bar(arg):
    print "bar called with ",arg
    gevent.sleep(2)
    print "bar called with %s finished" % arg
def foo(arg):
    waiting = random.randint(1, 10)
    print "foo called with %s : waiting: %s" % (arg, waiting)
    if arg % 2 == 0:
        raise Exception("foo:%s exception" % arg)
    gevent.sleep(waiting)
    gs = gevent.spawn(bar, arg)
    gs.join()
    print "foo called with %s finished" % arg
def you_callback():
    print "you callback"
    gevent.sleep(10)
    print "you callback finished"
def you():
    print "you called"
    gs = gevent.spawn(you_callback)
    gs.join()
    gevent.sleep(5)
    print "you finished"
def on_succ(msg, greenlet):
    print "succeed", msg
    gs = gevent.spawn(you)
    gs.join()
def on_fail(msg, greenlet):
    print "fail", msg
def demo_link(args):
    gs = [gevent.spawn(foo, arg) for arg in args]
    [g.link_value(partial(on_succ, "succ")) for g in gs]
    [g.link_exception(partial(on_fail, "fail")) for g in gs]
    gevent.joinall(gs)

demo_link
