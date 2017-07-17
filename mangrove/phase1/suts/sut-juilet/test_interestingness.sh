#!/bin/bash
# this script will be run by creduce in order to determine interestingness
# of reduced programs. it should not take any argument and it should only
# return 0 (interesting) or 1 (not interesting)

#update according to your enviroment.
cp /Users/ugurmeryem/Juliet/testcasesupport/std_testcase_io.h . > tmp 2>&1;
cp /Users/ugurmeryem/Juliet/testcasesupport/std_testcase.h . > tmp 2>&1;

# Step 1 of interestingness; here we perform our interestingness test
# which is calling the SCA to check the warning under consideration.
# This step is essential
cppcheck CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05.c  > tmp 2>&1;
var=$(cat tmp);

if [[ "$var" != *"Memory leak: data"* ]]; then
   exit 1;
fi


gcc -c CWE761_Free_Pointer_Not_at_Start_of_Buffer__wchar_t_fixed_string_05.c -I /Users/ugurmeryem/Juliet/testcasesupport > tmp 2>&1;

var=$(cat tmp);
if [[ "$var" == *"error"* ]]; then
   exit 1;
fi


exit 0;