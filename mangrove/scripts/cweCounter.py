#!/usr/bin python

import nltk

CWEs={'CWE114':0, 'CWE121':0, 'CWE122':0, 'CWE123':0, 'CWE124':0, 'CWE126':0, 'CWE127':0, 'CWE134':0, 'CWE15':0, 'CWE176':0, 'CWE188':0, 'CWE190':0, 'CWE191':0, 'CWE194':0, 'CWE195':0, 'CWE196':0, 'CWE197':0, 'CWE222':0, 'CWE223':0, 'CWE226':0, 'CWE23':0, 'CWE242':0, 'CWE244':0, 'CWE247':0, 'CWE252':0, 'CWE253':0, 'CWE256':0, 'CWE259':0, 'CWE272':0, 'CWE273':0, 'CWE284':0, 'CWE319':0, 'CWE321':0, 'CWE325':0, 'CWE327':0, 'CWE328':0, 'CWE338':0, 'CWE36':0, 'CWE364':0, 'CWE366':0, 'CWE367':0, 'CWE369':0, 'CWE377':0, 'CWE390':0, 'CWE391':0, 'CWE396':0, 'CWE397':0, 'CWE398':0, 'CWE400':0, 'CWE401':0, 'CWE404':0, 'CWE415':0, 'CWE416':0, 'CWE426':0, 'CWE427':0, 'CWE440':0, 'CWE457':0, 'CWE459':0, 'CWE464':0, 'CWE467':0, 'CWE468':0, 'CWE469':0, 'CWE475':0, 'CWE476':0, 'CWE478':0, 'CWE479':0, 'CWE480':0, 'CWE481':0, 'CWE482':0, 'CWE483':0, 'CWE484':0, 'CWE500':0, 'CWE506':0, 'CWE510':0, 'CWE511':0, 'CWE526':0, 'CWE534':0, 'CWE535':0, 'CWE546':0, 'CWE561':0, 'CWE562':0, 'CWE563':0, 'CWE570':0, 'CWE571':0, 'CWE587':0, 'CWE588':0, 'CWE590':0, 'CWE591':0, 'CWE605':0, 'CWE606':0, 'CWE615':0, 'CWE617':0, 'CWE620':0, 'CWE665':0, 'CWE666':0, 'CWE667':0, 'CWE672':0, 'CWE674':0, 'CWE675':0, 'CWE676':0, 'CWE680':0, 'CWE681':0, 'CWE685':0, 'CWE688':0, 'CWE690':0, 'CWE758':0, 'CWE761':0, 'CWE762':0, 'CWE773':0, 'CWE775':0, 'CWE78':0, 'CWE780':0, 'CWE785':0, 'CWE789':0, 'CWE832':0, 'CWE835':0, 'CWE843':0, 'CWE90':0}

file_content = open('codeData/bad.c', 'r')
counter = {'badpositive':0, 'goodpositive':0}
for line in file_content:
	if 'CWE134' in line:
		print line
	else: continue
	tokens = nltk.word_tokenize(line)
	size=len(tokens)
	if 'CWE134' == tokens[size-2]:
		counter[tokens[size-1]]+=1

