from greenlet import greenlet

def introduction():
    def test1():
        print 12
        gr2.switch()
        print 34

    def test2():
        print 56
        gr1.switch()
        print 78

    gr1 = greenlet(test1)
    gr2 = greenlet(test2)
    gr1.switch()

def switch():
    """
    g.switch(*args, **kwargs)
    Switches execution to the greenlet g, sending it the given arguments. As a special case, if g did not start yet, then it will start to run now.
    """
    def test1(x, y):
        print "x:", x, "y:", y
        z = gr2.switch(x + y)  # sending x+y to gr2
        print "test1", z
    def test2(u):
        print "test2", u
        gr1.switch(42)

    gr1 = greenlet(test1)
    gr2 = greenlet(test2)
    # switches between greenlets occur when method switch() called(jump
    # to the greenlet whose switch is called). During a switch, an object
    # or an exception is "sent" to the target greenlet.

    gr1.switch("hello", "world")  # sending hello, world to gr1
switch()
