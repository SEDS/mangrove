#!/usr/bin python 

import nltk

file_content = open("bad.c").read()
tokens = nltk.word_tokenize(file_content)

dict={}
for token in tokens:
	if token not in dict:
		dict[token] = 1;

dictStr="{"
counter=10000
for key in dict:
    wordIndex= ''.join(['\'',key, '\': ', str(counter), ', ', '\n'])
    dictStr +=wordIndex
    counter+=1

dictStr+="}"

print dictStr
