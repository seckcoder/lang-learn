'''Context Manager simulation'''
import traceback
class MyException(Exception):
    pass
class TraceBlock():
    def message(self, args):
        print 'running', args
    def __enter__(self):
        print 'starting with block'
        return self
    def __exit__(self, exc_type, exc_value, exc_tb):
        if exc_type is None:
            print 'exit normally'
        else:
            return False #re-raise

with TraceBlock() as action:
    action.message('hello world')
    print 'reached'

def foo9():
    raise TypeError('foo9')
def foo8():
    foo9()
def foo7():
    foo8()
def foo6():
    foo7()
def foo5():
    foo6()
def foo4():
    foo5()
def foo3():
    foo4()
def foo2():
    foo3()
def foo1():
    foo2()

try:
    with TraceBlock() as action:
        action.message('hello world with exception')
        foo1()
        print 'not reached'
except MyException as e:
    print e
