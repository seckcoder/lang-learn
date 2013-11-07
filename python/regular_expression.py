#!/usr/bin/env python
import re
m = re.search("c", "abcdef")
if m:
	print 'search' 
m = re.match("c", "abcdef")
if m:
	print 'match'
m = re.match(r"(?P<first_name>\w+\?\w+) (?P<last_name>\w+)", "Is?sac Newton")
if m:
	print m.group("first_name"), m.group("last_name")


