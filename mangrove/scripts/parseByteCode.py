#!/usr/bin/env python

import cPickle, re, os, string, random
from os.path import isfile, join

dict={}
warnings={}

def tokenize(sample):
	sample = re.sub('in\smethod:get\w+,\sat\sline:\d+,\sinst:.*\n','', sample)
	sample = re.sub('in\smethod:\w+,\sat\sline:\d+,\sinst:(\d+\s=\s)*','', sample)
	sample = re.sub('<\s*Application,\s*','<', sample)
	sample = re.sub('Ljava/\w*/','', sample)
	sample = re.sub('(\d+,)*\d*\s@\d+\sexception:\d+',' ', sample)
	sample = re.sub('@\d+',' ', sample)
	
	helpDict={'\"':' " ', '\(':' ( ', '\)': ' ) ','\[':' [ ','\]': ' ] ','\{': ' { ', '\'':' \' ', ';':' ; ', 
			'==':' == ', '<':' < ', '>':' > ', '!':' ! ', '\+\+':' ++ ', '--':' -- ', '\+': ' + ', '-':' - ', 
			'\#':' # ', '\*':' * ', ',':' , ', '\!=':' != ', '&':' & ', '=':' = ', '@':' @ ', ':':' : ', '\.':' . '} # '':'  '
	for key in helpDict:
		sample = re.sub(key, helpDict[key], sample)
	sample = re.sub('=\s=','==', sample)
	sample = re.sub('>\s>','>>', sample)
	sample = re.sub('<\s<','<<', sample)
	sample = re.sub('/\s\*','/*', sample)
	sample = re.sub('\*\s/','*/', sample)
	sample = re.sub(' \d{6} ',' N ', sample)
	sample = re.sub(' \d{5} ',' N ', sample)
	sample = re.sub(' \d{4} ',' N ', sample)
	sample = re.sub(' \d{3} ',' N ', sample)
	sample = re.sub('\s+', ' ', sample) # remove multi spaces
	

	tokens=sample.split()
	for t in tokens:
		if not dict.has_key(t):
			dict[t] = 0
		dict[t] = dict[t]+1
	return sample.strip()
	

def processSliceFiles(directory,saveToFileName):
	falsePattern = re.compile(".*(good|true)positive.txt")
	saveToFile = open(saveToFileName, 'w')
	files = [join(directory, f) for f in os.listdir(directory) if isfile(join(directory, f))]
	for fileName in files:
		with open(fileName) as file: lines = file.readlines()
		sample=''
		for line in lines: 
			sample+=line.rstrip()+' '
		
		label='truepositive' if falsePattern.match(fileName) else 'falsepositive'
		saveToFile.write(tokenize(sample)+' '+label+'\n')

if __name__ == '__main__':
	julietDir = '/Users/ukoc/mangrove/phase2/slices/juliet/'
	julietFile='/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89JulietSlices.java'
	processSliceFiles(julietDir,julietFile)
	
	owaspDir = '/Users/ukoc/mangrove/phase2/slices/owasp/'
	owaspFile='/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89OwaspSlices.java'

	warningFile='/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89OwaspCategories.txt'
	with open(warningFile) as file: wLines = file.readlines()
	for line in wLines:
		tuple=line.split(',')
		warnings[tuple[0]]='truepositive' if tuple[1]==tuple[2] else 'falsepositive'

	processSliceFiles(owaspDir,owaspFile)
	for key, value in dict.iteritems():
		if value>5 : print key+'\t'+str(value)
