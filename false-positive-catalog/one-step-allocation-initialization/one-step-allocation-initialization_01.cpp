// NOT derived from Juliet
// Original structure: one-step-allocation-initialization

// #################################################################
// ## Variant: one-step-allocation-initialization_01
// ## CHANGE: Separated initialization from allocation
// #################################################################

#include <stdio.h>

int main(void)
{
    // CHANGE: Moved initialization to a separate line.
    int * data = new int;
    *data = 7;
    
    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: none
    printf("int: %d\n", *data);

    delete data;
    return 0;
}