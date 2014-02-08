import sub_module
sub_module.a.foo()   # Note this will raise an error. To solve this, you should 
                     # import a in sub_module/__init__.py
