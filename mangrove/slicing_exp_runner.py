#!/usr/bin python

import os, string, subprocess
	
filepath='/Users/ukoc/mangroveL/sa-lstm/data/java/CWE89JulietStatsBalanced.txt'
with open(filepath) as file: lines = file.readlines()
for line in lines:
	print subprocess.call(["java", "-jar" ,"slicer.jar", line.rstrip()])
	#commands.getstatusoutput(' ' + line.rstrip())