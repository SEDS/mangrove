// Juliet CWE415_Double_Free__malloc_free_char_32.c
// Original structure: lack-of-specificity/dereference-non-ptr

// #################################################################
// ## Variant: dereference-non-ptr_01
// ## CHANGE: Use pointer as recipient of assignment
// #################################################################

#include <stdlib.h>

int main(void)
{
    char * data;
    // CHANGE: Use another ordinary pointer (instead of pointer-to-pointer) on LHS of assignment.
    char * dataPtr = data;

    data = (char *)malloc(100*sizeof(char));
    free(data);

    // CodeSonar FP: none
    // scan-build FP: none
    // Cppcheck FP: none
    dataPtr = data;
    return 0;
}