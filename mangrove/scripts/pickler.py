#!/usr/bin python

import cPickle

file_content = open("codeData/codeData.txt").read()
with open('codeData/imdb.pkl', 'wb') as handle:
  cPickle.dump(file_content, handle, -1)
