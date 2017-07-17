#!/bin/bash

rm -fr /Users/ukoc/juliet-reduced-testcases;
rm -fr /tmp/scan-build*;

mv /Users/ukoc/juliet/testcases /Users/ukoc/juliet-reduced-testcases;
rm -fr /home/ukoc/juliet;
unzip -q /Users/ukoc/Juliet_Test_Suite_v1.2_for_C_Cpp.zip -d /Users/ukoc/juliet;

#rm -fr ~/juliet-logs ; mkdir ~/juliet-logs;
