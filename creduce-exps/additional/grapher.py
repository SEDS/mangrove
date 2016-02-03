#!/opt/local/bin/python2.7

import networkx as nx
import os, sys

fileName=sys.argv[1]
log = open(fileName, 'r').read().splitlines()

passCount=0
passSeq=[]
passEffectMap={}
passIn=''
passOut=''
passResult=1
while log:
  line=log.pop(0)
  if line.__contains__('===< '):
    if passCount>0:
      passEffectMap[passName+str(passCount)]=(passIn,passOut,passResult)
    passName=line[5:-5]
    passSeq.append(passName)
    passIn=''
    passOut=''
    passResult=1
    passCount += 1
  elif line.startswith('<',0,1):
    passIn +=line[1:]
  elif line.__contains__('delta test failure'):
    passResult=0

mykeys=passEffectMap.keys()
for key in mykeys:
  print '%s --> (' % (key)
  for v in passEffectMap[key]:
    print ' %s' % (v)
  print ')'