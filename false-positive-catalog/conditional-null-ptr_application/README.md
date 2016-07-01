## Application of `conditional null ptr` FP structure

Our [false positive catalog](https://github.iu.edu/SEDS/mangrove/wiki/FP-Hierarchy) shows that global variables in conditions can cause tools to give FPs (see `conditional null ptr` pattern). Global variables are discouraged in modern object-oriented programming, but the `conditional null ptr` pattern we identified is still relevant without using global variables. This code gives an example.

A class constructor sets a private variable to true, which is never changed in the object's lifetime. A SCA tool should recognize this and understand that reads of the variable will always return true. However, using the variable in conditions gives FPs.

### Results

* **CodeSonar:** Flags FP
* **scan-build:** Flags FP*
* **Cppcheck:** Flags FP

*For some reason, scan-build flags the FP only if the `ClassCondition.cpp` file is tested individually (i.e. not by testing against `make`). That is, the following command gives the FP:

```
$ scan-build g++ -c ClassCondition.cpp
ClassCondition.cpp:22:26: warning: Dereference of null pointer (loaded from variable 'data')
    printf("Data: %d\n", *data);
                         ^~~~~
1 warning generated.
scan-build: 1 bug found.

```

However, this command gives no FP:

```
scan-build make
```

**This scan-build behavior is important to document so that we are careful in the future when running scan-build. Even if scan-build does not issue a warning when running against `make`, scan-build *could* issue warnings when running against files individually.**