#!/bin/bash

gcc -c bzip2.c > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" == *"error: "* ]]; then
   #echo "Does not compile!";
   exit 1;
fi

scan-build gcc -c bzip2.c > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" != *": warning: The left operand of '==' is a garbage value"* ]]; then
   #echo "Warning went away!";
   exit 1;
fi

exit 0;


#bzip2.c:2350:17: warning: The left operand of '==' is a garbage value
#if (yy[0] == ll_i) {

#bzip2.c:2373:19: warning: Assigned value is garbage or undefined
#rtmp  = yy[1];