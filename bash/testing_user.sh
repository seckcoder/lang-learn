#!/bin/bash

# (()) is for arithmetic expressions
if (( 0 && 1))
then
    echo 'evaluates to nonzero'
else
    echo 'evaluates to 0'
fi

n=1; let --n && echo "True" || echo "False"
n=1; let n-- && echo "True" || echo "False"

a=32
(( t = a<45?7:11 ))
echo $t


# [] is a synonym for test, which tests file types and compare strings

if [ -f testing_user.sh ]; then
    echo "testing_user.sh not exist"
fi

if test -f testing_user.sh; then
    echo 'testing_user.sh not exist'
fi

if [ false ]; then
    echo 'although false return non-zero error code, but in `test false`,
        test just see false as an expression'
fi

# [[ is better than [ since it can used for logical combination
a=3
b=5
if [[ (a -gt 0) && !(b -lt 0) ]]; then
    echo 'yes'
fi
