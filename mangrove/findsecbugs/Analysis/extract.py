import xml.etree.ElementTree as ET
import re
import random
from os import listdir
import math

C = [0.0,0.0]
ByteCodeCount = {}
totalByteCodes = [0.0,0.0]
codes = [[],[]]
prob = [[],[]]

d = '../reports_owasp/'
def readSamples(d):
	C = [0.0,0.0]
	ByteCodeCount = {}
	totalByteCodes = [0.0,0.0]
	codes = [[],[]]
	for f in listdir(d):
		if not f.endswith('.xml'):
			continue
		tree = ET.parse(d+f)
		root = tree.getroot()
		code = ''
		for child in root.iter("String"):
			if child.get('role')=='Method Bytecode':
				code = child.get('value')
				break
		code = re.split('\s*\d+:\s+',code)[1:-1]
		code = [bc.split()[1] if bc.split()[0]=='invokevirtual' or bc.split()[0]=='new' else bc.split()[0] for bc in code ]
		name = f.split('.')[0]
		isTrue = 1 if name.endswith('TP') or name.endswith('bP') else 0
		# if random.random()>0.8:
		# 	codes[isTrue].append(code)
		# 	continue
		codes[isTrue].append(code)
		C[isTrue] = C[isTrue]+1
		for l in code:
			if not l in ByteCodeCount:
				ByteCodeCount[l] = [0,0]
			ByteCodeCount[l][isTrue] = ByteCodeCount[l][isTrue]+1
			totalByteCodes[isTrue] = totalByteCodes[isTrue]+1
	return C, ByteCodeCount, totalByteCodes, codes


C, ByteCodeCount, totalByteCodes, codes  = readSamples('../reports_owasp/')
# C, ByteCodeCount, totalByteCodes, codes  = readSamples('../reports_juliet/s01/')

# C, ByteCodeCount, totalByteCodes, _  = readSamples('../reports_owasp/')
# C, ByteCodeCount, totalByteCodes, _  = readSamples('../reports_juliet/s04/')
# _, _, _, codes  = readSamples('../reports_juliet/s04/')
# _, _, _, codes  = readSamples('../reports_owasp/')

# for l in ByteCodeCount:
# 	if ByteCodeCount[l][0]>1 or ByteCodeCount[l][1]>1:
# 		print(l, ByteCodeCount[l][0], ByteCodeCount[l][1])
bad = [l for l in ByteCodeCount if (ByteCodeCount[l][0]<2 and ByteCodeCount[l][1]<2) ]
	# or 0.3<(1.0*ByteCodeCount[l][0]/(ByteCodeCount[l][0]+ByteCodeCount[l][1]))<0.6]
for l in bad:
	del ByteCodeCount[l]

f = open('results.txt', 'w')
for l in ByteCodeCount:
	f.write(l+' '+str(ByteCodeCount[l][0])+' '+str(ByteCodeCount[l][1])+'\n')

f.close()

def calcProb(codes, C, ByteCodeCount, totalByteCodes):
	prob = []
	for code in codes:
		logb = math.log(1.0*C[0]/(C[1]+C[0]))
		loga = math.log(1.0*C[1]/(C[1]+C[0]))
		for l in code:
			est = [1.0, 1.0]
			if l in ByteCodeCount:
				est = [ByteCodeCount[l][0]+1, ByteCodeCount[l][1]+1]
			else:
				print(l)
			logb = logb + math.log(est[0] / (totalByteCodes[0]+len(ByteCodeCount)))
			loga = loga + math.log(est[1] / (totalByteCodes[1]+len(ByteCodeCount)))
		p=1.0/(1.0+math.exp(logb-loga))
		prob.append(p)
	return prob

prob= [ calcProb(codes[0],C,ByteCodeCount,totalByteCodes) , calcProb(codes[1],C,ByteCodeCount,totalByteCodes) ]


t = 0.5
total = len([i for i in prob[1]])+len([i for i in prob[0]])
good = len([i for i in prob[1] if i>=t])+len([i for i in prob[0] if i<t])
print('Accuracy: '+str(1.0*good/total))
print('Recall: '+str(1.0*len([i for i in prob[1] if i>=t])/len([i for i in prob[1]])))
print('Precision: '+str(1.0*len([i for i in prob[1] if i>=t])/(len([i for i in prob[1] if i>=t])+len([i for i in prob[0] if i>=t]))))
# print(1.0*good/total)
# print(1.0*len([i for i in prob[1] if i>=t])/len([i for i in prob[1]]))
# print(1.0*len([i for i in prob[0] if i<t])/len([i for i in prob[0]]))
# print(len([i for i in prob[1] if i>=t]))
# print(len([i for i in prob[0] if i<t]))

# t = 0.1
# total = len([i for i in prob[1]])+len([i for i in prob[0]])
# good = len([i for i in prob[1] if i>=t])+len([i for i in prob[0] if i<t])
# print(1.0*good/total)
# print(1.0*len([i for i in prob[1] if i>=t])/len([i for i in prob[1]]))
# print(1.0*len([i for i in prob[0] if i<t])/len([i for i in prob[0]]))
# print(len([i for i in prob[1] if i>=t]))
# print(len([i for i in prob[0] if i<t]))


