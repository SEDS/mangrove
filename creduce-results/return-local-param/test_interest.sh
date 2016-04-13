#!/bin/bash
# this script will be run by creduce in order to determine interestingness
# of reduced programs. it should not take any argument and it should only
# return 0 (interesting) or 1 (not interesting)

#update according to your enviroment.
cp /home/zachary/SCATE/testcasesupport/std_testcase_io.h . > tmp 2>&1;
cp /home/zachary/SCATE/testcasesupport/std_testcase.h . > tmp 2>&1;

# Step 1 of interestingness; here we perform our interestingness test
# which is calling the SCA to check the warning under consideration.
# This step is essential
cppcheck CWE665_Improper_Initialization__char_cat_21.c  > tmp 2>&1;
var=$(cat tmp);

if [[ "$var" != *"Pointer to local array variable returned"* ]]; then
   exit 1;
fi


gcc -c CWE665_Improper_Initialization__char_cat_21.c -I /home/zachary/SCATE/testcasesupport > tmp 2>&1;

var=$(cat tmp);
if [[ "$var" == *"error"* ]]; then
   exit 1;
fi


exit 0;
