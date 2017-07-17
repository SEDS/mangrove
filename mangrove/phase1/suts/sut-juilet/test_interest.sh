#!/bin/bash
# this script will be run by creduce in order to determine interestingness
# of reduced programs. it should not take any argument and it should only
# return 0 (interesting) or 1 (not interesting)

# here we perform our interestingness test
# which is calling the SCA to check the warning under consideration.
# This step is essential
var=$(scan-build gcc -c CWE121_Stack_Based_Buffer_Overflow__CWE193_char_declare_loop_07.c -I /Users/ugurmeryem/Dropbox/mangroveL/sut-juilet/ -D OMITBAD 2>&1 | cat);

if [[ "$var" != *": warning: Dereference of undefined pointer value"* ]]; then
   exit 1;
fi
if [[ "$var" != *"data[i] = source[i]"* ]]; then
   exit 1;
fi

exit 0;