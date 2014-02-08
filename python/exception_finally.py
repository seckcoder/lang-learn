
"""Never return value in finally"""

def bar():
    try:
        return True
    finally:
        return False

def foo():
    try:
        raise Exception
    finally:
        return False

print bar()
print foo()
