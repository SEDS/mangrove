import xml.etree.ElementTree as ET
import re
import random
from os import listdir
import math
import itertools

C = [0.0,0.0]
ByteCodeCount = {}
totalByteCodes = [0.0,0.0]
codes = [[],[]]
prob = [[],[]]
ID = [[],[]]

badSignalDict = ['goodG2B', 'dataGoodG2B', 'goodG2BSink', 'badSink', 'staticReturnsTrueOrFalse',
	'asd', 'staticReturnsTrue', 'privateReturnsTrue', 'ne', 'badSource', 's01', 's02', 's03', 's04',
	'Ltestcases', 'SeparateClassRequest', 'C',
	'Object', 'return', 'helpers', 'doSomething', 'esapi', 'ESAPI', 'eq', 'ge',
	# 'getTheValue'
	]

weaksignalDict = [line.strip('\n') for line in open('weakSignals.txt','r')]

def isBadWord(l):
	if l in badSignalDict or l.isdigit() or 'CWE89' in l or 'BenchmarkTest' in l or l in weaksignalDict:
		return True
	else:
		return False

def sortedInLine(l):
	l.sort()
	return l[0]+'&'+l[1]+'&'+l[2]

def readSamples(d):
	C = [0.0,0.0]
	ByteCodeCount = {}
	totalByteCodes = [0.0,0.0]
	codes = [[],[]]
	ID = [[],[]]
	counter = 0
	for f in listdir(d):
		counter = counter + 1
		print(counter,' of ',1178+1193)


		if not f.endswith('.txt'):
			continue
		filee = open(d+f, 'r')
		
		# code = [re.findall(r"[\w]+", line) for line in filee]
		code = [re.findall(r'[\w\/]+', re.sub(r'in\smethod:\w+,\sat\sline:\d+,\sinst:', '' ,line)) for line in filee]
		code = [x for sublist in code for x in sublist]
		name = f.split('.')[0]
		isTrue = 1 if name.endswith('truepositive') or name.endswith('badpositive') else 0

		code = [x for x in code if not isBadWord(x)]
		#Remove for first analysis
		# code = code + [code[i]+'&'+code[j]+'&'+code[k] for i in range(len(code)) for j in range(i+1,len(code)) for k in range(j+1,len(code))]
		# code = code + [sortedInLine([code[i],code[j],code[k]]) for i in range(len(code)) for j in range(i+1,len(code)) for k in range(j+1,len(code)) if
		# 	code[i]!=code[j] and code[i]!=code[k] and code[j]!=code[k]]

		# if random.random()>0.8:
		# 	codes[isTrue].append(code)
		# 	continue
		codes[isTrue].append(code)
		ID[isTrue].append(f)
		C[isTrue] = C[isTrue]+1
		for l in code:
			if not l in ByteCodeCount:
				ByteCodeCount[l] = [0,0]
			ByteCodeCount[l][isTrue] = ByteCodeCount[l][isTrue]+1
			totalByteCodes[isTrue] = totalByteCodes[isTrue]+1
	return C, ByteCodeCount, totalByteCodes, codes, ID


C, ByteCodeCount, totalByteCodes, codes, ID  = readSamples('../owasp/')
# C, ByteCodeCount, totalByteCodes, codes, ID  = readSamples('../juliet/')
# _, _, _, codes, ID  = readSamples('../owasp/')
# _, _, _, codes, ID  = readSamples('../juliet/')

#Just for first analysis
# bad = [l for l in ByteCodeCount if (ByteCodeCount[l][0]<100 and ByteCodeCount[l][1]<100) 
# 	or 0.45<(1.0*ByteCodeCount[l][0]/(ByteCodeCount[l][0]+ByteCodeCount[l][1]))<0.55]

#Second analysis
bad = [l for l in ByteCodeCount if (ByteCodeCount[l][0]<100 and ByteCodeCount[l][1]<100) 
	or 0.3<(1.0*ByteCodeCount[l][0]/(ByteCodeCount[l][0]+ByteCodeCount[l][1]))<0.6]
# for l in bad:
# 	del ByteCodeCount[l]

f = open('results.txt', 'w')
for l in ByteCodeCount:
	f.write(l+' '+str(ByteCodeCount[l][0])+' '+str(ByteCodeCount[l][1])+'\n')

f.close()


def calcProb(codes, C, ByteCodeCount, totalByteCodes):
	prob = []
	counter = 0
	for code in codes:
		counter = counter + 1
		print(counter,' of ',len(codes))

		logb = math.log(1.0*C[0]/(C[1]+C[0]))
		loga = math.log(1.0*C[1]/(C[1]+C[0]))
		for l in code:
			if isBadWord(l):
				continue
			est = [1.0, 1.0]
			if l in ByteCodeCount:
				est = [ByteCodeCount[l][0]+1, ByteCodeCount[l][1]+1]
			# else:
				# continue
				# print(l)
			logb = logb + math.log(est[0] / (totalByteCodes[0]+len(ByteCodeCount)))
			loga = loga + math.log(est[1] / (totalByteCodes[1]+len(ByteCodeCount)))
		if logb-loga<=0:
			p=1.0/(1.0+math.exp(logb-loga))
		else:
			p = math.exp(loga-logb)/(1.0+math.exp(loga-logb))
		prob.append(p)
	return prob

prob= [ calcProb(codes[0],C,ByteCodeCount,totalByteCodes) , calcProb(codes[1],C,ByteCodeCount,totalByteCodes) ]


t = 0.5
total = len([i for i in prob[1]])+len([i for i in prob[0]])
good = len([i for i in prob[1] if i>=t])+len([i for i in prob[0] if i<t])
print('Accuracy: '+str(1.0*good/total))
print('Recall: '+str(1.0*len([i for i in prob[1] if i>=t])/len([i for i in prob[1]])))
print('Precision: '+str(1.0*len([i for i in prob[1] if i>=t])/(len([i for i in prob[1] if i>=t])+len([i for i in prob[0] if i>=t]))))


f = open('distTP.txt', 'w')
for i in range(len(prob[1])):
	f.write(ID[1][i]+' '+str(prob[1][i])+'\n')
f.close()

f = open('distFP.txt', 'w')
for i in range(len(prob[0])):
	f.write(ID[0][i]+' '+str(prob[0][i])+'\n')
f.close()

def getProb(c):
	# global ByteCodeCount
	return 1.0*(ByteCodeCount[c][0]+1)/(totalByteCodes[0]+len(ByteCodeCount)), 1.0*(ByteCodeCount[c][1]+1)/(totalByteCodes[1]+len(ByteCodeCount)), 

def printCodeColored(I, ID, isTP, codes):
	i = ID[isTP].index(I)
	code = codes[isTP][i]
	print(prob[isTP][i])
	f = open(I+'info.txt','w')
	A = 0.5
	B = 0.5
	logb = math.log(1.0*C[0]/(C[1]+C[0]))
	loga = math.log(1.0*C[1]/(C[1]+C[0]))
	for c in code:
		# A = A*getProb(c)[1]
		# B = B*getProb(c)[0]
		# print(getProb(c))
		# print(A/(A+B))
		# f.write(c+' '+str(getProb(c)[0])+' '+str(getProb(c)[1])+'\n')
		if (not 0.4<1.0*ByteCodeCount[c][0]/(ByteCodeCount[c][0]+ByteCodeCount[c][1])<0.6):
			f.write(c+' '+ str(1.0*ByteCodeCount[c][0]/(ByteCodeCount[c][0]+ByteCodeCount[c][1]))+'\n')
		# f.write(c+'\n')
	f.close()
	# print(A/(A+B))

printCodeColored('BenchmarkTest09066truepositive.txt' , ID, 1, codes)





