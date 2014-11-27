#!/bin/bash

arr[11]=23
arr[32]=34
echo ${arr[11]}

arr[4]=`expr ${arr[11]} + ${arr[32]}`
echo ${arr[4]}
echo; echo; echo;


arr=( one two three [17]=seven)

echo ${arr[0]}
echo ${arr[17]}
