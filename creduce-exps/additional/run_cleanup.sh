#!/bin/bash

rm -fr /home/ukoc/juliet-reduced-testcases;
rm -fr /tmp/scan-build*;

mv /home/ukoc/juliet/testcases /home/ukoc/juliet-reduced-testcases;
rm -fr /home/ukoc/juliet;
unzip -q /home/ukoc/Juliet_Test_Suite_v1.2_for_C_Cpp.zip -d /home/ukoc/juliet;

#rm -fr ~/juliet-logs ; mkdir ~/juliet-logs;
