#!/usr/bin/env python

# repr
print 'repr ---- '
i = [1, 2, 3]
print repr(i)
#string formating
print "String Formating----"
print "%s --- %s --- %s --- %s" % (42, 33.22223, [1, 2, 3], "Dior Peng")
vars = {'name': 'Dior Peng', 'Property': 'Diors', 'age': 22, 
		'sex' : 'unknown', 'exp': 3.1415926}
dior_peng = "name: %(name)s, exp: %(exp)-5.3f | %(exp)e | %(exp)+5.3f, age: %(age)05d" % vars
print dior_peng
