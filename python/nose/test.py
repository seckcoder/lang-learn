import unittest2

def add(a,b):
    return a+b

def test_add():
    #simple test functions
    assert add(2,3) == 5


class TestCase(unittest2.TestCase):
    def test_add(self):
        """Test case subclasses can also be detected by nose"""
        assert add(2,3) == 5


class TestClass(object):
    """Test class is a class defined in a test module that matches [Tt]estxxx"""
    def test_add(self):
        assert add(2,3) == 5


def check_add(a, b):
    assert add(a, b) == (a+b)

def test_adds():
    for i in xrange(0,5):
        """Test Generators. (generate series of test casess)"""
        yield check_add, i, i*2
