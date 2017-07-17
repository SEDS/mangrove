#!/bin/bash

var=$(scan-build gcc -c bzip2.c 2>&1 | cat);
if [[ "$var" == *"error: "* ]]; then
   exit 1;
fi

if [[ "$var" != *": warning: The left operand of '==' is a garbage value"* ]]; then
   exit 1;
fi

if [[ "$var" != *"yy[0] == ll_i"* ]]; then
exit 1;
fi

exit 0;

#bzip2.c:2350:17: warning: The left operand of '==' is a garbage value
#if (yy[0] == ll_i) {

#bzip2.c:2373:19: warning: Assigned value is garbage or undefined
#rtmp  = yy[1];
