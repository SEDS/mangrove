// Juliet s01/CWE690_NULL_Deref_From_Return__char_malloc_09.c
// Structure: conditional-mem-leak-external-var

// *** REQUIRES TEST CASE SUPPORT FILES ***

#include "std_testcase.h"

// GLOBAL_CONST_TRUE is defined as follows in io.c
// const int GLOBAL_CONST_TRUE = 1;
// If the global variable is defined within this file (still globally), the FPs go away (for scan-build and Cppcheck).

int main(void)
{
    char * data;
    data = (char *)malloc(20*sizeof(char));
    if(GLOBAL_CONST_TRUE)
    {
    	// CodeSonar FP: none
        // scan-build FP: (warning) Potential leak of memory pointed to by 'data'
        // Cppcheck FP: (error) Memory leak: data
        free(data);
    }
    // Note: Adding a return statement here causes the Cppcheck FP to go away.
}
