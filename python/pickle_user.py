import pickle

class FooClass(object):
    def __init__(self):
        self.attr_1 = 'this is a string'
        self.attr_2 = 23223

    def __str__(self):
        return "%s %s" % (self.attr_1, self.attr_2)


foostr = pickle.dumps(FooClass())
obj = pickle.loads(foostr)
print obj.attr_1,obj.attr_2
