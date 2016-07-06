# False Positive Catalog

Here are code samples of the FP patterns listed on the [wiki](https://github.iu.edu/SEDS/mangrove/wiki/FP-Hierarchy).

Each sample gives the minimized structure to reproduce the false warning. Samples are commented with the Juliet test cases from which they are obtained. We simplified the stuctures (e.g. replacing variables with literal constant values, combining variable declaration and initialization, etc.) as long as the FP did not go away or was converted to a TP.

Samples are commented with the false warnings that the SCA tools gave.

Some FP patterns are organized in sub-directories. These patterns contain *changes*, which are small edits to the original FP pattern. The motiviation for *changes* is to try to alter the SCA tool result. The purpose of *changes* is to more closely identify what is causing the FP. Each change is numbered arbitrarily and described with a brief phrase (the latter being annotated in the source code). Each change is performed independently against the original code.

### Current Toolset

* CodeSonar v 4.1p4
* scan-build (with Clang v 3.8.0 and gcc/g++ v 5.2.1) - from our observations, the gcc/g++ version seems to make a difference in the warnings that scan-build gives.
* Cppcheck v 1.72

### Severity of Warnings

By default, Cppcheck reports only *errors*. Other types of warnings can be turned on with the `--enable=` argument. The command below enables errors, warnings, and all style checks:

    cppcheck --enable=warnings,style filename.cpp

This is importance because enabling these lower-severity messages in Cppcheck may be needed to produce warnings of the same severity that other tools report by default.