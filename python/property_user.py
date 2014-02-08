#!/usr/bin/python

class Parrot(object):
    def __init__(self):
        self._voltage = 0
        self._name = "parrot liwei"

    @property
    def voltage(self):
        return self._voltage
    @voltage.setter
    def voltage(self, new_value):
        self._voltage = new_value

    def get_name(self):
        return self._name
    def set_name(self, value):
        self._name = value
    name = property(get_name, set_name, doc='''get set for name''')

p = Parrot()
print p.voltage
p.voltage = 12
print p.voltage
print p.name
p.name = 'parrot seckcoder'
print p.name
