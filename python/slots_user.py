#!/usr/bin/python

'''
__slots__ reserves enough space in each instance to hot a value for each variable
when you have __slots__, __dict__ willnot be created for each instance.
__slots__ is used in new-style class only.
There is an excellent snippet about slots on stackoverflow: http://stackoverflow.com/questions/1816483/python-how-does-inheritance-of-slots-in-subclasses-actually-work
'''


def demo1():
    class StudySlots(object):
        __slots__ = 'attr1', 'attr2'
        def attr1(self):
            return 'attr1'

    class StudySlots2(object):
        pass

    print '------------------------------------------'
    print 'dir of StudySlots'
    print '\t', dir(StudySlots)
    print 'dir of StudySlots2'
    print '\t', dir(StudySlots2)
    study_case1 = StudySlots()
    study_case2 = StudySlots2()
    print '------------------------------------------'
    print 'attr1 of study_case1:', study_case1.attr1()
    print 'We can set slot attribute of study_case1'
    study_case1.attr2 = 10
    print '\tattr2:', study_case1.attr2
    try:
        study_case1.attr3 = 10
    except:
        print 'We cannot set non-slot attribute of study_case2'


def demo2():
    
    # Demo of inheritance for slots
    class Human(object):
        __slots__ = ('__name',)
        def __init__(self, name):
            self.__name = name
        @property
        def name(self):
            return self.__name

        @name.setter
        def name(self, value):
            self.__name = value

    class Student(Human):
        __slots__ = ('__class',)
        def __init__(self, name, _class):
            super(Student, self).__init__(name)
            self.__class = _class

        @property
        def cclass(self):
            return self.__class
        
        @cclass.setter
        def cclass(self, value):
            self.__class = value

        def __str__(self):
            return "name:{0}; class:{1}".format(self.name, self.cclass)

    print "This demo shows that slots can be inherited. However, you should\n\
be careful about inheritance with slots. Since: When inheriting from a\n\
class without __slots__, the __dict__ attribute of that class will always\n\
be accessible, so a __slots__ definition in the subclass is meaningless."

    obj = Student('liwei', '1-1')
    print obj
    obj.name = 'seckcoder'
    print obj
    obj.cclass = '2-1'
    print obj
    try:
        obj.test_attr = 10
    except AttributeError:
        print "We can't set non-slot attribute"
    
demo2()
