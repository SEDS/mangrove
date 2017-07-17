#!/usr/bin/env python

import cPickle, re, os, string, random
from os.path import isfile, join

dict={}
def tokenize(sample):
	# in the following modifications order is important
	sample = re.sub('<','', sample) # simple remove 
	sample = re.sub(' >','>', sample)
	sample = re.sub('>\d+','> N', sample)
	sample = re.sub('<','', sample)
	sample = re.sub('>','', sample)
	sample = re.sub(';',' ', sample)
	sample = re.sub('\)',' ', sample)
	sample = re.sub('\(',' ', sample)
	sample = re.sub(', to iindex=\d+','', sample) # remove common string
	sample = re.sub('\d+\s*,\s*\d+','', sample) # remove N, N
	#sample = re.sub('\s*,\s*','.', sample) # unify path and method name
	#sample = re.sub('\d+\[\d+\] = N','', sample) # arraysote
	#sample = re.sub('\d+\[\d+\]','', sample)
	#sample = re.sub('\d+','N', sample) # remove two digit numbers
	sample = re.sub('\s+', ' ', sample) # remove multi spaces

	#add2Dict(sample)
	return sample.strip()

def obfucate(sample):

	#owasp specific, no harm for juliet
	sample = re.sub('Lorg/owasp/benchmark/(helpers|testcode)/(\w+\.)*\w+ ', 'UNK_CALL ', sample) # UNK_CALL
	sample = re.sub('Lorg/owasp/benchmark/(helpers|testcode)/\w+\$\w+\.\w+ ', 'UNK_CALL ', sample) # UNK_OBJ
	sample = re.sub('Lorg/owasp/benchmark/(helpers|testcode)/\w+ ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('Lorg/owasp/benchmark/(helpers|testcode)/\w+\$\w+ ', 'UNK_OBJ ', sample) # UNK_OBJ

	#juliet specific, no harm for owasp
	sample = re.sub('Ltestcases(/\w+)*((\.|\$)*\w*)* ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('Ltestcasesupport(/\w+)*((\.|\$)*\w*)* ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('Ltestcasesupport/IO.logger.logging/Logger ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('logging/Level.WARNING.logging/Level ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('logging/Level ', 'UNK_OBJ ', sample) # UNK_OBJ
	sample = re.sub('logging/Logger.log ', 'UNK_OBJ ', sample) # UNK_OBJ

	#accumuloa specific, no harm for owasp
	sample = re.sub(' Lorg/apache/accumulo(/\w*)*\.\w+ ', ' UNK_CALL ', sample)
	sample = re.sub(' Lorg/apache/accumulo(/\w*)*(\$\w+) ', ' UNK_OBJ ', sample) 
	sample = re.sub(' Lorg/apache/accumulo(/\w*)*(\$\w*)*(\.\w*)* ', ' UNK_CALL ', sample)
	
def add2Dict(sample):
	# create dict in the fly
	tokens=sample.split()
	for t in tokens:
		if not dict.has_key(t):
			dict[t] = 0
		dict[t] = dict[t]+1
	

def processSliceFiles(directory,saveToFileName):
	falsePattern = re.compile(".*(good|true)positive.txt")
	saveToFile = open(saveToFileName, 'w')
	files = [join(directory, f) for f in os.listdir(directory) if isfile(join(directory, f))]
	for fileName in files:
		with open(fileName) as file: lines = file.readlines()
		#if 'BenchmarkTest09066' not in fileName and 'BenchmarkTest16536' not in fileName:
		#if 'BenchmarkTest13402' not in fileName and 'BenchmarkTest08439' not in fileName and 'BenchmarkTest10215' not in fileName and 'BenchmarkTest13486' not in fileName and 'BenchmarkTest10245' not in fileName and 'BenchmarkTest10295' not in fileName:
		#	continue
		sample=''
		for line in lines:
			if 'invokespecial' in line:
				continue
			line = re.sub('in\smethod:\w+(\$\d+)*,\sat\sline:\d+,\sinst:(\d+\s=\s)*','', line) #remove meta info
			line = re.sub('<\s*Application,\s*','<', line) #remove Application part
			line = re.sub('Ljava/\w*/','', line) # remove java lib prefix
			line = re.sub('Ljavax/servlet/\w*/','', line) #remove javax lib prefix
			line = re.sub('\s*>\s*\d*(,\d*)* @\d* exception:\d*','>', line) # remove exception info
			line = re.sub('@\d+',' ', line) # remove @ numbers
			line = re.sub(';',' ', line)
			line = re.sub('>',' ', line)
			line = re.sub('<',' ', line)
			line = re.sub('\)',' ', line)
			line = re.sub('\(',' ', line)
			line = re.sub(', to iindex=\d+','', line) # remove common string
			line = re.sub('\d+\s*,\s*\d+','', line) # remove N, N
			if 'invoke' in line:
				line= re.sub(', ','.', line)
			elif 'switch' in line:
				line='switch'
			elif 'putfield' in line:
				line= re.sub('\d+\.','', line)
			#elif 'getstatic' in line:
			#	line='getstatic'
			#elif 'arrayload' in line:
			#	line='arrayload'
			
			line = re.sub('\s+', ' ', line) # remove multi spaces
			sample+=line.rstrip()+'\n'
		
		label='truepositive' if falsePattern.match(fileName) else 'falsepositive'
		saveToFile.write(sample+' '+label+'\n')

if __name__ == '__main__':
	outDir='/Users/ukoc/mangrove/phase2/lstm/data/java/'
	sliceDir='/Users/ukoc/mangrove/phase2/slices/'
	#processSliceFiles(sliceDir+'juliet/', outDir+'CWE89JulietSlices.java')
	#processSliceFiles(sliceDir+'injectionOwasp/', outDir+'InjectionOwaspSlices2.java') #_2Sample
	processSliceFiles(sliceDir+'accumulo',outDir+'AccumuloSlices.java')

	for key, value in dict.iteritems():
		print key+'\t'+str(value)