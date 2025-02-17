# Assertion-structure representation of a pattern

The assertion-structure representation is a new way to represent false positive
patterns. This representation has two parts:

 1. Structure: based on the program flow graph.

 2. Assertions: conditions that must hold in various points along the program graph.

Until now we have been considering only structure for representing patterns, but
this may not be complete. Our false positive checkers have been giving some
false positive themselves. Perhaps including assertions will help us more fully
represent false positive patterns.


## `condition-mem-leak` checker false positives

Below are four *checker* false positives in minimized form that we obtained from
sampling. From these checker false positives, we hope to glean assertions that
will help us better represent the *tool* false positive patterns. Here is how we
had defined the structure of this pattern:
[condition-mem-leak](https://github.iu.edu/SEDS/mangrove/wiki/Conditional-Mem-Leak-FP).

### `condition-mem-leak_checker-FP1.cpp`

Here the allocation happens within the body of a (different) `if` statement.
This second `if` condition checks the same global variable that is in the
condition that guards the deallocation. This `if` statement body always
executes, but Cppcheck and scan-build do not flag the warning, so the checker
warning is a false positive. Here the assertion is that the allocation must
occur outside an `if` statement body.

### `condition-mem-leak_checker-FP2.cpp`

The structure is a complicated version of FP1. It seems that user-defined types
and methods have caused the tools *not* to flag the false positive, so the
checker warning is a false positive. (One difference in this FP2 structure from
FP1 is that the two global variables in conditions are different, and the
deallocation happens in the `else` clause. Interestingly, the allocation code
does *not* have to be moved before the first `if` statement to introduce the
tool false positive. This is because deallocation happens in the `else` clause,
unlike FP1.) We still need to design an assertion from this example--perhaps it
will involve restrictions on user-defined types and methods.

### `condition-mem-leak_checker-FP3.cpp`

Here the allocation happens within the *same* `if` statement body where the
memory is freed. No memory leak can occur. The checker still flags this
structure as a false positive pattern. The checker does not seem to be checking
that the allocation occurs before the `if` statement, as the structure of this
pattern specifies. We should be able to modify the checker with this simple fix.
Therefore, we should be able to represent this variation structurally, without
assertions.

### `condition-mem-leak_checker-FP4.c`

Here the global variable is declared with a `const` declaration, causing neither
Cppcheck nor scan-build to flag the false positive. The simple assertion we come
up with when analyzing this example is that the global variable cannot be
declared with a `const` declaration.
