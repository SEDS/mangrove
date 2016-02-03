#!/bin/bash

#update according to your enviroment.
cp /Users/ugurmeryem/Dropbox/mangroveL/cppcheck/std_testcase_io.h . > tmp 2>&1;
cp /Users/ugurmeryem/Dropbox/mangroveL/cppcheck/std_testcase.h . > tmp 2>&1;
gcc -c CWE401_Memory_Leak__wchar_t_realloc_18.c > tmp 2>&1;

var=$(cat tmp);
if [[ "$var" == *"error: "* ]]; then
#echo "Does not compile!";
   exit 1;
fi

cppcheck CWE401_Memory_Leak__wchar_t_realloc_18.c > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" != *"Common realloc mistake: 'd' nulled but not freed upon failure"* ]]; then
#echo "Warning went away!";
   exit 1;
fi

exit 0;
