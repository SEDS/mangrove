#!/usr/bin/env python2.7

import xml.etree.ElementTree as ET
import re, os, string, sys
from os.path import isfile, join

dict={}
def processFile(fileName):
        tree = ET.parse(fileName)
        root = tree.getroot()
        code=''
        for child in root.iter("String"):
	       if child.get('role')=='Method Bytecode':
                        code = child.get('value')
                        break
        code = re.split('\s*\d+:\s+',code)[1:-1]
        code = [' '.join(bc.split()[0:2]) if 'invoke' in bc.split()[0] or bc.split()[0]=='new' else bc.split()[0] for bc in code ]
        return ' '.join(code)

def tokenize(sample):
        sample = re.sub('in\smethod:get\w+,\sat\sline:\d+,\sinst:.*\n','', sample)
        sample = re.sub('in\smethod:\w+,\sat\sline:\d+,\sinst:(\d+\s=\s)*','', sample)
        sample = re.sub('<\s*Application,\s*','<', sample)
        sample = re.sub('Ljava/\w*/','', sample)
        sample = re.sub('(\d+,)*\d*\s@\d+\sexception:\d+',' ', sample)
        sample = re.sub('@\d+',' ', sample)
        
        helpDict={'\"':' " ', '\(':' ( ', '\)': ' ) ','\[':' [ ','\]': ' ] ','\{': ' { ', '\'':' \' ', ';':' ; ', 
                        '==':' == ', '<':' < ', '>':' > ', '!':' ! ', '\+\+':' ++ ', '--':' -- ', '\+': ' + ', '-':' - ', 
                        '\#':' # ', '\*':' * ', ',':' , ', '\!=':' != ', '&':' & ', '=':' = ', '@':' @ ', ':':' : '}#, '\.':' . '} # '':'  '
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
        

#        tokens=sample.split()
 #       for t in tokens:
  #              if not dict.has_key(t):
   #                     dict[t] = 0
    #            dict[t] = dict[t]+1
        return sample.strip()

def trimReport(fileName):
        tree = ET.parse(fileName)
        root = tree.getroot()
        for summary in root.findall('FindBugsSummary'):
                root.remove(summary)
        for err in root.findall('Errors'):
                root.remove(err)
        for proj in root.findall('Project'):
                root.remove(proj)
        for feat in root.findall('ClassFeatures'):
                root.remove(feat)
        for his in root.findall('History'):
                root.remove(his)
        tree.write(fileName)

if len(sys.argv)>1:
	trimReport(sys.argv[1])
else:
	pattern = re.compile(".*\.xml")
	#julietDir="reports_juliet"
	owaspDir="reports_owasp"
	directory=owaspDir
	xmlFiles = [join(directory, f) for f in os.listdir(directory) if (isfile(join(directory, f)) and pattern.match(f))] 
	for fileName in xmlFiles:
                name = fileName.split('.')[0]
                label = 'truepositive' if name.endswith('TP') or name.endswith('bP') else 'falsepositive'
                t=tokenize(processFile(fileName))
		print t + ' '+ label

        #for key, value in dict.iteritems():
        #       if value>5 : print key+'\t'+str(value)