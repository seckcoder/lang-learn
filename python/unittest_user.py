#!/usr/bin/env python
import unittest
import random

class TestSequenceFunctions(unittest.TestCase):
    def setUp(self):
        self.seq = range(10)
    def test_shuffle(self):
        random.shuffle(self.seq)
        self.seq.sort()
        self.assertEqual(self.seq, range(10))
        self.assertRaises(TypeError, random.shuffle, (1,2,3))
    def test_choice(self):
        element = random.choice(self.seq)
        self.assertTrue(element in self.seq)
def test_case():
    print 'haha'
if __name__ == '__main__':
    unittest.main()
