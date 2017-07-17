#!/usr/bin/env python

import pickle

with open('/Users/ukoc/Downloads/imdb.dict.pkl', 'rb') as f:
    data = pickle.load(f)
    print data