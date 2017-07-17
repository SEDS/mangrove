#!/bin/bash

rm a.out > tmp 2>&1;
gcc smple-freedtwice.c > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" == *"error: "* ]]; then
   #echo "Does not compile";
   exit 1;
fi

scan-build gcc -c smple-freedtwice.c > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" != *"warning: Attempt to free released memory"* ]]; then
   #echo "Warning went away";
   exit 1;
fi

exit 0;

#wont run anyway
./a.out > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" != *"Done!"* ]]; then
   #echo "Test Case Failed";
   exit 1;
fi
