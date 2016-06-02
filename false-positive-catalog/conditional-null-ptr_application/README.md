## Application of `conditional null ptr` FP structure

Our [false positive catalog](https://github.iu.edu/SEDS/mangrove/wiki/FP-Catalog#global-variables) shows that global variables in conditions can cause tools to give FPs (see `conditional null ptr` pattern). Global variables are discouraged in modern object-oriented programming, but the `conditional null ptr` pattern we identified is still relevant without using global variables. This code gives an example.

A class constructor sets a private variable to true, which is never changed in the object's lifetime. A SCA tool should recognize this and understand that reads of the variable will always return true. However, using the variable in conditions gives FPs.

### Results

**Cppcheck:** Flags FP

**scan-build:** Does *not* flag FP