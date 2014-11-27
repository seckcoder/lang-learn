#!/bin/bash

function usage ()
{
    printf "usage:%s [ -a | -b ] file1 ... filen\n" $0
} >&2  # redirect the output to stderr

# return values
# Method 1
function max ()
{
    local HIDN  # local variable, can't visit from outside
    if [ $1 -gt $2 ]
    then
        BIGR=$1
    else
        BIGR=$2
    fi
    HIDN=5
}
max 128 4
echo $BIGR
# Method 2
function max_2 ()
{
    if [ $1 -gt $2 ]
    then
        echo $1
    else
        echo $2
    fi
}

BIGR=$(max_2 128 4)
echo $BIGR

function foo ()
{
    echo "here"
    return 1  # return is used as function's exit. When you call exit in function,
              # the whole program will exit
    echo "cannot reach"
}
foo
echo $?
