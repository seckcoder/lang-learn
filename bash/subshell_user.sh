#!/bin/bash

# subshell is a process launced by a shell. 
# Directory changes made in a subshell do not carry over to the parent shell.
(
cd ~
echo `pwd`
)
echo `pwd`
