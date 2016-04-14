## C-Reduce results compared to manual reduction

Here are examples comparing C-Reduce code reduction to the minimal sample that still contains the false positive of interest. Each directory has the results of one FP pattern. These results use Cppcheck 1.72.

Overall the results show that, **for the transformations applied**, C-Reduce performs mostly trivial reduction and rarely reduces code within the function of interest. 

In some cases, C-Reduce removes the `main()` function so that the original control flow is lost. The manually-reduced snippets preserve control flow, but these differences aren't very important. We are mainly concerned with reduction within the function of interest.

Manual reduction consists of removing whole lines or comments. Further reduction is possible in some cases (e.g. replacing variables with literal values), but this is more aggressive. We cannot assume C-Reduce would do this.

### Files

Here are the files within each directory:

  * ***`<test-case-name>`***`.orig.c` - Original code (e.g. `CWE617_Reachable_Assertion__fgets_01.orig.c`)
  * ***`<test-case-name>`***`.c` - Reduced code using C-Reduce (e.g. `CWE617_Reachable_Assertion__fgets_01.c`)
  * ***`<directory-name>`***`.c` - Reduced code by hand (minimal sample that still compiles and contains the FP) (e.g. `modest-buffer-use.c`)
  * `reduce` - C-Reduce command used to do the reduction (includes the transformations and their priorities)
  * `test_interest.sh` - interestingness script