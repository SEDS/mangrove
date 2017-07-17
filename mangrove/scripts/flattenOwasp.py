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
	sample = re.sub('= =','==', sample)
	sample = re.sub('> >','>>', sample)
	sample = re.sub('< <','<<', sample)
	sample = re.sub('/ \*','/*', sample)
	sample = re.sub('/ /','//', sample)
	sample = re.sub('\* /','*/', sample)
	sample = re.sub(' \d{2-5} ',' N ', sample)
	sample = re.sub(' //WARNINGLINE',' WARNINGLINE ', sample)
	sample = re.sub(' //goodpositive ',' goodpositive ', sample)
	sample = re.sub(' //badpositive ',' badpositive ', sample)
	return sample.strip()

if __name__ == '__main__':
	for filepath in glob.glob('/Users/ukoc/workspace/Mutants/src/main/java/org/owasp/benchmark/testcode/*.java'):
		sample=''
		isSampleLine=False
		with open(filepath) as file: lines = file.readlines()
		for line in lines: 
			if isSampleLine and '// ' not in line:
				sample+=line.rstrip()+' '
			elif 'public class ' in line:
				isSampleLine=True
		print obfuscate(tokenize(sample))