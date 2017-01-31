// Juliet CWE476_NULL_Pointer_Dereference__class_11.cpp
// Structure: conditional-mem-leak-external-function

// *** REQUIRES TEST CASE SUPPORT FILES ***

#include "std_testcase.h"

int main(void)
{
    int * data = new int;

    if (globalReturnsTrue())
    {
        delete data;
    }
    // CodeSonar FP: none
    // scan-build FP: (warning) Potential leak of memory pointed to by 'data'
    // Cppcheck FP: (error) Memory leak: data

    // Note: Adding a return statement here causes the Cppcheck FP to go away.
}
