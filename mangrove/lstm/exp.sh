#!/bin/bash

dimensions=( 2 3 4 8 16 32 64 128)

for i in "${dimensions[@]}" 
do
	THEANO_FLAGS="floatX=float32" python lstm.py $i "test"
done