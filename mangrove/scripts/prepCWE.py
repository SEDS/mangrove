#!/usr/bin python

import cPickle, re, os, string, random, glob
from os.path import isfile, join

def get_immediate_subdirectories(a_dir):
	return [name for name in os.listdir(a_dir) if os.path.isdir(os.path.join(a_dir, name))]

def obfuscate(sample):
	randStr=''.join(random.choice(string.ascii_lowercase) for _ in xrange(3))
	sample = re.sub('\s+', ' ', sample) # remove multi spaces
	#sample = re.sub('good', randStr, sample) #remove the word good 
	#sample = re.sub('bad', randStr, sample) #remove the word bad
	sample = re.sub('/\*[^;/]* \*/', '', sample) #remove most of the comments old pattern /\*[\w*:,\(\)-*\d\s_]* \*/
	sample = re.sub('\"[\w+,\(\)\s]+\"', '" STRING "', sample) #unify print out strings
	return sample.strip()

def tokenize(sample):
	helpDict={'\"':' " ', '\(':' ( ', '\)': ' ) ','\[':' [ ','\]': ' ] ','\{': ' { ', '\'':' \' ', ';':' ; ', '==':' == ', '<':' < ', '>':' > ', 
	'!':' ! ', '\+\+':' ++ ', '--':' -- ', '\+': ' + ', '-':' - ', '\#':' # ', '\*':' * ', ',':' , ', '\!=':' != ', '&':' & ', '=':' = ', '\.':' . '} # '':'  '
	for key in helpDict:
		sample = re.sub(key, helpDict[key], sample)
	sample = re.sub('=\s=','==', sample)
	sample = re.sub('>\s>','>>', sample)
	sample = re.sub('<\s<','<<', sample)
	sample = re.sub('/\s\*','/*', sample)
	sample = re.sub('\*\s/','*/', sample)
	sample = re.sub(' \d{2-5} ',' N ', sample)
	return sample.strip()

def processGood(lines, warningLine):
	goodPattern = re.compile("void good\w*\(")
	record=False
	sample=''
	counter=0
	sampleFirstLine=0
	for line in lines: 
		counter=counter+1
		if goodPattern.search(line):
			sampleFirstLine=counter
			record=True
			sample+=line.rstrip()+' '
		elif 'main(' in line:
			break
		elif record:
			sample+=line.rstrip()+' '
	print obfuscate(tokenize(sample)) + ' goodpositive'


def processBad(lines, warningLine):
	goodPattern = re.compile("void good\w*\(")
	badPattern = re.compile("void bad\w*\(")
	record=False
	sample=''
	counter=0
	sampleLastLine=0
	for line in lines: 
		counter=counter+1
		if badPattern.search(line):
			record=True
			sample+=line.rstrip()+' '
		elif goodPattern.search(line):
			sampleLastLine=counter
			break
		elif record and '// ' not in line:
			sample+=line.rstrip()+' '
	print obfuscate(tokenize(sample)) +' badpositive'
	
if __name__ == '__main__':
	warningFile='data/java/CWE89JulietStatsBalanced.txt'
	julietDir = '/Users/ukoc/workspace/Juliet4J/mutants/'
	with open(warningFile) as file: lines = file.readlines()
	for line in lines:
		(fileName,lineNumber,desc,label)=line.rstrip().split(",")
		with open(julietDir+fileName[4:]) as file: lines = file.readlines()
		if label == 'goodpositive':
			processGood(lines, int(lineNumber))
		else:
			processBad(lines, int(lineNumber))