# Static Code Analysis Warning Logs

This directory contains raw warnings logs from static code analysis tools 
over code bases. Logs may contain comments at the beginning to provide more
information about the tool or code base (e.g. version).

## Filename convention

The log files names are in the following format:

    code-base_tool-name_other-details.txt

## Sampling results

The file `cppcheck-juliet-warning-sampling.xlsx` shows the static code analysis tool 
warning instances that we sampled to obtain an approximate frequency for the Cppcheck
false positives in the Juliet test suite. We used a 95% confidence threshold and have 
reported these frequency results throughout the 
[FP Catalog](https://github.iu.edu/SEDS/mangrove/wiki/FP-Catalog).

*The sampling files for CodeSonar and scan-build are coming soon.*