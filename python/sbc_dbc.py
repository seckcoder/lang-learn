#!/usr/bin/env python
# -*- coding: utf_8 -*-

def strQ2B(ustring):
	rstring = ""
	for uchar in ustring:
		inside_code = ord(uchar)
		if inside_code == 0x3000:
			inside_code = 0x0020
		else:
			inside_code -= 0xFEE0
		if inside_code < 0x0020 or inside_code > 0x7E:
			rstring += uchar
		else:
			rstring += unichr(inside_code)
	return rstring
def strB2Q(ustring):
	rstring = ""
	for uchar in ustring:
		inside_code = ord(uchar)
		print inside_code
		if inside_code < 0x0020 or inside_code > 0x7e:
			print '1', uchar
			rstring += uchar
		if inside_code == 0x0020:
			print '2'
			inside_code = 0x3000
		else:
			print '3'
			inside_code += 0xfee0
		rstring += unichr(inside_code)
	return rstring

a = strB2Q("abc123")
print a
