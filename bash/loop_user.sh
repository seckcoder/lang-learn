#!/bin/bash

for arg in 1 2 3 4; do
    echo $arg
done

arr=( one two three four )

for arg in ${arr[@]}; do
    echo $arg
done

for f in /etc/*
do
    echo $f
done
