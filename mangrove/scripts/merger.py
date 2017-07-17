#!/usr/bin/env python

import cPickle, re, os, string, random
from os.path import isfile, join

dict={}

if __name__ == '__main__':
	reports='/Users/ukoc/mangrove/phase2/lstm/data/java/InjectionOwaspFB.csv'
	owaspLabels='/Users/ukoc/mangrove/phase2/lstm/data/java/InjectionOwaspStats.csv'
	with open(owaspLabels) as file: lines = file.readlines()
	for line in lines:
		tokens=line.rstrip().split(',')
		dict[tokens[0]]=tokens
		
	print 'class,line,callee,type,label'
	with open(reports) as file: lines = file.readlines()
	for line in lines:
		tokens=line.rstrip().split(',')
		if tokens[0] not in dict:
			continue
		entry=dict[tokens[0]]
		if entry[1]==tokens[3]:
			print line.rstrip()+','+entry[2]+'positive'