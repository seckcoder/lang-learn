"""
Test Suite
"""

from test_core import TestCore
import unittest


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(
            TestCore)
    unittest.TextTestRunner(verbosity=2).run(suite)
