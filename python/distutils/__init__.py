"""usage of distutils"""

setup(packages="A list of packages. you can get this through find_packages function. celery has a greate example on packages option",
      py_modules = "Used to list individual modules",
      test_suite = "if specify `nose.collector` as the test_suite, then I can run the test through python setup.py nosetests")
