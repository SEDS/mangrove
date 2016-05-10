// Juliet CWE476_NULL_Pointer_Dereference__class_11.cpp
// Structure: function-conditional-null-ptr

// *** REQUIRES TEST CASE SUPPORT FILES ***

#include "std_testcase.h"
#include <stdio.h>

int main(void)
{
    TwoIntsClass * data;
    if (globalReturnsTrue())
    {
        data = new TwoIntsClass;
        data->intOne = 5;
    }
    // scan-build FP: warning: Dereference of undefined pointer value
    // Cppcheck FP: error: Uninitialized variable: data
    printf("data: %d\n", data->intOne);
    delete data;
}