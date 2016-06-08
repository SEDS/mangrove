# False Positive Catalog

Here are code samples of the FP structures listed on the [wiki](https://github.iu.edu/SEDS/mangrove/wiki/FP-Hierarchy).

Each sample gives the minimized structure to reproduce the false warning. Samples are commented with the Juliet test cases from which they are obtained. We simplified the stuctures (e.g. replacing variables with literal constant values, combining variable declaration and initialization, etc.) as long as the FP did not go away or was converted to a TP.

Samples are commented with the false warnings that the SCA tools gave.

### Current Toolset

* Cppcheck v 1.72

* scan-build (with Clang v 3.8.0 and gcc/g++ v 5.2.1) - from our observations, the gcc/g++ version seems to make a difference in the warnings that scan-build gives.

### Severity of Warnings

Most of our work using Cppcheck was done by considering only *errors*. Other warnings can be turned on with the `--enable=` argument. This command enables errors (by default), warnings, and all style checks:

    cppcheck --enable=warnings,style filename.cpp

This is importance because enabling these lower-severity messages in Cppcheck may be needed to produce warnings of the same severity as scan-build. In the examples where Cppcheck did *not* give a FP, we  may need to retest after enabling lower-severity checks.