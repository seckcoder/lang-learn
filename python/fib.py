def fibonacci(n):
    a = 1
    b = 1
    if n <= 1:
        return 1
    else:
        for i in xrange(n-1):
            tmp = a + b
            a = b 
            b = tmp
        return b

print fibonacci(2)
print fibonacci(40)
