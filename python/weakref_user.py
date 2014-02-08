import weakref

def simple_demo():
    class obj(object):
        def __init__(self, a):
            self.a = a
        def __repr__(self):
            return "obj:{0}".format(self.a)

    o = obj(3)
    r = weakref.ref(o)
    if r():
        print "weakref's referent is alive"
        print "weakref's reference's references/proxies is ", weakref.getweakrefs(o)
    del o
    if r():
        print "weakref's referent is not alive"
        print "weakref's reference's references/proxies is ", weakref.getweakrefs(o)

def with_slots():
    class Entry(object):
        __slots__ = (
            'fun', 'args', 'kwargs', 'tref','__weakref__'
        )
        def __init__(self, fun, args=None, kwargs=None):
            self.fun = fun
            self.args = args or []
            self.kwargs = kwargs or {}
            self.tref = weakref.proxy(self)
        def __call__(self):
            return self.fun(*self.args, **self.kwargs)
    def hello(name, age):
        print "Hello, I'm {0} aged {1}".format(name, age)
    e = Entry(hello, args=("liwei",), kwargs={"age":23})
    print e.tref
with_slots()
