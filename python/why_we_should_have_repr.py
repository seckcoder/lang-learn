The %s specifier converts the object using str(), and %r converts it using repr().

For some objects such as integers, they yield the same result, but repr() is special in that (for types where this is possible) it conventionally returns a result that is valid Python syntax, which could be used to unambiguously recreate the object it represents.

Here's an example, using a date:

>>> d = datetime.date.today()
>>> str(d)
'2011-05-14'
>>> repr(d)
'datetime.date(2011, 5, 14)'
Types for which repr() doesn't produce Python syntax include those that point to external resources such as a file, which you can't guarantee to recreate in a different context.
