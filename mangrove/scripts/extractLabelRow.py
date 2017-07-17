#!/usr/bin python

import cPickle, re, os, string, random
from os.path import isfile, join

labelRow=''
with open('codeData/bad.c') as file: lines = file.readlines()
for line in lines: 
	if 'badpositive' in line:
		labelRow += '0, '
	else:
		labelRow += '1, '
	
print labelRow

