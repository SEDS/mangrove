#!/bin/bash

cp /home/ukoc/juliet/testcasesupport/std_testcase_io.h . > tmp 2>&1;
cp /home/ukoc/juliet/testcasesupport/std_testcase.h . > tmp 2>&1;

scan-build gcc -c -I /home/ukoc/juliet/testcasesupport -D OMITBAD file-name > tmp 2>&1;
var=$(cat tmp);
if [[ "$var" != *"warning-description-line1"* ]]; then
   exit 1;
fi

if [[ "$var" != *"warning-description-line2"* ]]; then
    exit 1;
fi

exit 0;
