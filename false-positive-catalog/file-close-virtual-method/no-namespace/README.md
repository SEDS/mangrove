# `no-namespace` File-Close-Virtual-Method FP variation

**The no-namespace version (using `open()`) does *not* give a FP in CodeSonar.**

When not using a user-defined namespace, CodeSonar does ***not*** flag a FP (or using the `std` namespace). More research may still be needed to learn how CodeSonar behaves when only *part* of the code is in the user-defined namespace.
