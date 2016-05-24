// Juliet CWE588_Attempt_to_Access_Child_of_Non_Structure_Pointer__class_09.cpp
// Pattern: condition-external-const-var

// This pattern is a combination of "Global Variables" category and "Externally Defined Symbols" category.
// If global variable is defined locally, the FPs go away (for scan-build and Cppcheck)

#include "std_testcase.h"
#include <stdio.h>

// GLOBAL_CONST_TRUE defined as follows in io.c
// const int GLOBAL_CONST_TRUE = 1;

int main(void)
{
    int * intPtr;
    // Simplified the data structure from a class in Juliet to an integer.
    int intVar = 7;
    if(GLOBAL_CONST_TRUE)
    {
        intPtr = &intVar;
    }

    // scan-build FP: (warning) Dereference of undefined pointer value
    // Cppcheck FP: (error) Uninitialized variable: intPtr
    printf("int: %d\n", *intPtr);
}