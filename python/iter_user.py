#-*- coding=utf-8 -*-


'''
# TODO(liwei) : 
1. How to create an iterator?
2. How to stop an iteration in the for loops?
3. in contextmanager, we will use yield to throw something to "with as", 
can we use this as an iterator?
'''


# How to create an iterator? and how to stop an iteration in the for loops
def demo_create_iterator():
    # method 1: use yield
    def gensquares(N):
        for i in xrange(N):
            yield i**2
    
    # gensquares is a generator function which returns a generator object
    for sq in gensquares(5):
        print sq,

    print
    # method 2: use indexing.(Note not all iterators support indexing)
    class SquareGenerator(object):
        def __getitem__(self, index):
            return index**2
    
    sq_gentor = SquareGenerator()
    # this is actually not an iterator but instead an object support indexing.
    # iterators is prefered to indexing when both can be used since the previous
    # will typically be more efficient.
    for i in xrange(5):
        print sq_gentor[i],
    print
    # method 2 continue: use __getitem__ to implement iteration

    # I have to admit that this method is really weird.
    # This works since the for statement works by repeatedly indexing
    # a sequence from zero to higher indexes, until an out-of-bounds
    # exception(IndexError) is detected

    class stepper:
        def __getitem__(self, i):
            return self.data[i]

    X = stepper()
    X.data = "spam"
    for item in X:
        print item,
    print 
    # method 3: use iter(or __iter__)
    
    # what does iter actually do?
    # iter actually trys to find an __iter__ method of the object,
    # and method __iter__ returns an iterator object(which should have
    # a function named next)
    l = [1,2,3,4]
    it = iter(l)
    print it.next()

    class Squares(object):
        def __init__(self, stop):
            self.value = -1
            self.stop = stop

        def __iter__(self):
            return self   # return self(which contains method next)

        def next(self):
            if self.value >= self.stop-1:
                raise StopIteration  # in iterators, use StopIteration instead of IndexError to stop iteration
                #raise IndexError
            self.value += 1
            return self.value ** 2
    
    for i in Squares(5):
        print i,


    # To sum up, method 1 is the simplest and has code easist to read.
    # method 2 is better than method 3. Try to use yield when possible.

import contextlib
# Demo for the difference between yield in contextmanager and yield to create
# iterator
def demo_contextmanager_yield():

    # The following is a typical usage of context manager
    class Resource(object):
        def acquire(self):
            pass
        def release(self):
            pass

        def do_something(self):
            pass

    @contextlib.contextmanager
    def acquire_res():
        res = Resource()
        res.acquire()
        try:
            yield res
        except:
            res.release()
        
    # No context manager.(This is just for demo use. Don't do 
    # this in production)
    def acquire_res1():
        res = Resource()
        res.acquire()
        yield res
        res.release()

    with acquire_res() as res:
        # do something with res
        res.do_something()
    
    t = acquire_res()
    t1 = acquire_res1()
    # Note t and t1 is different.
    # If you look at the implementation of GeneratorContextManager, you'll
    # notice that GeneratorContextManager is not a generator at all. And
    # the resource yield in the contextmanager should be yield once only(that is,
    # we could call next once, and the second times StopIteration will be raised)
    # else an exception will be raised.
    print type(t), type(t1)

    # To sum up, we can't use the return value of yield in contextmanager
    # as an iterator, since it's not an iterator.


#demo_create_iterator()
