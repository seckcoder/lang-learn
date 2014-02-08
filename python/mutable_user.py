"""
Understanding mutable and immutable:
    You have to understand that Python represents all its data as objects.
    Some of these objects like lists and dictionaries are mutable, meaning you can change their content without changing their identity.
    Other objects like integers, floats, strings and tuples ... are objects that can not be changed. When you try to modify
    it's content, memory will be allocated.
    An easy way to understand that is to look at object ID.
    
    Therefore, Numbers, strings and tuples are immutable, while lists and dictionaries are mutable.

    Why numbers are immutable?
        When you do a = 1.0, the = operand is not wich create the float, but the 1.0 part of the line.
        Actually when you write 1.0 it is a shorthand for float(1.0) a constructor call returning a float object.
        
        
"""

a = 1.0
print id(a)
a += 1
print id(a)  # Note that id has changed, therefore we haven't changed the original object


a = [1,2,3]
print id(a)
a.append(4)
print id(a)  # Id hasn't changed
