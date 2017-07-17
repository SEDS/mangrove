#!/usr/bin/env python

from __future__ import print_function
from termcolor import colored
import state_below as sb
import c_array as ca
import f_array as fa
import h_array as ha
import term_colors as tc
import numpy as np
import sys

def getColorIndex(actualVal):
	val = 0
	if actualVal < 0.4 and actualVal > -0.4:
		val = 222
	elif actualVal < 0.8 and actualVal > -0.8:
		val = -1 if actualVal<0 else 1
	elif actualVal < 1.2 and actualVal > -1.2:
		val = -2 if actualVal<0 else 2
	elif actualVal < 1.6 and actualVal > -1.6:
		val = -3 if actualVal<0 else 3
	elif actualVal < 2 and actualVal > -2:
		val = -4 if actualVal<0 else 4
	else:
		val = -5 if actualVal<0 else 5
	return val

def getColorIndexForget(actualVal):
	val = 0
	if actualVal ==0:
		val = 230
	elif actualVal < 0.2 and actualVal > -0.2:
		val = -1 if actualVal<0 else 1
	elif actualVal < 0.4 and actualVal > -0.4:
		val = -2 if actualVal<0 else 2
	elif actualVal < 0.6 and actualVal > -0.6:
		val = -3 if actualVal<0 else 3
	elif actualVal < 0.8 and actualVal > -0.8:
		val = -4 if actualVal<0 else 4
	else:
		val = -5 if actualVal<0 else 5
	return val

def getColorIndexOutput(actualVal):
	val = 0
	if actualVal < 0.35 and actualVal > -0.35:
		val = 256	
	elif actualVal < 0.5 and actualVal > -0.5:
		val = -5 if actualVal<0 else 5
	elif actualVal < 0.7 and actualVal > -0.7:
		val = -4 if actualVal<0 else 4
	elif actualVal < 0.9 and actualVal > -0.9:
		val = -3 if actualVal<0 else 3
	else:
		val = -2 if actualVal<0 else 2
	return val

def getColorIndexOutput2(actualVal):
	val = 0
	if actualVal < 0.35 and actualVal > -0.35:
		val = 256	
	elif actualVal < 0.5 and actualVal > -0.5:
		val = 226 if actualVal<0 else 195
	elif actualVal < 0.7 and actualVal > -0.7:
		val = 227 if actualVal<0 else 159
	elif actualVal < 0.9 and actualVal > -0.9:
		val = 229 if actualVal<0 else 123
	else:
		val = 11 if actualVal<0 else 87
	return val

dict={}
dataFile='../data/java/CWE89OwaspSlices_2Sample2.java'
#dataFile='../data/java/CWE89OwaspByteCode_2Sample.java'
dictLines = open("../data/java/dictForSlicesOwasp.java").readlines()
for line in dictLines:
	keyValue=line.split()
	dict[keyValue[0]]=keyValue[1]
file_content = open(dataFile, 'r').readlines()
fileLen=len(file_content)
#values = np.asarray(ca.c5)
#values = np.asarray(fa.f5)
values = np.asarray(ha.h6)
#values = np.asarray(sb.state_below3)
for m in xrange(0,4):
	tc.print_color('                                                                                                                                                              ', bg=256) 
	tc.print_color('==============================================================================Cell '+str(m+1)+'==========================================================================', bg=255) 
	#tc.print_color('                                                                                                                                                              ', bg=254) 
	for lineNumber in xrange(0,fileLen):
		tokens=file_content[lineNumber].split()
		sampleLen=len(tokens)
		for tIndx in xrange(0,sampleLen):
			t=tokens[tIndx]
			if 'positive' in t:
				print(t)
				if 'truepositive' in t:
					tc.print_color('--------------------------------------------------------------------------------------------------------------------------------------------------------------')
				break
			val = getColorIndexOutput2(values[tIndx, lineNumber, m])
			#val = tc.rgb(-val, 0, 0) if val < 0 else tc.rgb(0, 0, val)
			if t not in dict:
				tc.print_color('UNK', bg=val, end=' ')
			else:
				tc.print_color(t, bg=val, end=' ')

if False:
	tc.print_color("", bg=256, end='\n') 
	tc.print_color("-1<=", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(2, 0, 0), end='')
	tc.print_color("<=-0.9<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(3, 0, 0), end='')
	tc.print_color("<=-0.7<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(4, 0, 0), end='')
	tc.print_color("<=-0.5<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(5, 0, 0), end='')
	tc.print_color("<=-0.35<", bg=256, end='') 
	tc.print_color("below threashold", bg=256, end='')
	tc.print_color("<=0.35<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(0, 0, 5), end='')
	tc.print_color("<=0.5<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(0, 0, 4), end='')
	tc.print_color("<0.7<=", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(0, 0, 3), end='')
	tc.print_color("<0.9<", bg=256, end='') 
	tc.print_color(" ", bg=tc.rgb(0, 0, 2), end='')
	tc.print_color("<=1", bg=256, end='') 
	tc.print_color("", bg=tc.rgb(0, 0, 0), end='\n')