#!/usr/bin/env python

import re

def tokenize(sample):
	helpDict={'\"':' " ', '\(':' ( ', '\)': ' ) ','\[':' [ ','\]': ' ] ','\{': ' { ', '\'':' \' ', ';':' ; ', '==':' == ', '<':' < ', '>':' > ', 
	'!':' ! ', '\+\+':' ++ ', '--':' -- ', '\+': ' + ', '-':' - ', '\#':' # ', '\*':' * ', ',':' , ', '\!=':' != ', '&':' & ', '=':' = ', '\.':' . ', 
	'@':' @ ', ':':' : ', '/':' / ' } # '':'  '
	for key in helpDict:
		sample = re.sub(key, helpDict[key], sample)
	sample = re.sub('= =','==', sample)
	sample = re.sub('> >','>>', sample)
	sample = re.sub('< <','<<', sample)
	sample = re.sub('/ \*','/*', sample)
	sample = re.sub('/ /','//', sample)
	sample = re.sub('\* /','*/', sample)
	sample = re.sub('    ',' ', sample)
	sample = re.sub('   ',' ', sample)
	sample = re.sub('  ',' ', sample)
	sample = re.sub(' \d{5} ',' N5 ', sample)
	sample = re.sub(' \d{4} ',' N4 ', sample)
	sample = re.sub(' \d{3} ',' N3 ', sample)
	sample = re.sub(' \d{2} ',' N2 ', sample)
	return sample.strip()

with open("/Users/ukoc/mangrove/phase2/lstm/data/java/CWE89JulietCTE_2.java") as file: lines = file.readlines()
for line in lines: 
	print tokenize(line)

		