// Juliet: CWE690_NULL_Deref_From_Return__struct_realloc_04.c

#include "std_testcase.h"

// Removing the `const` declaration from this global variable introduces the FP
// for both Cppcheck and scan-build.
static const int STATIC_CONST_TRUE = 1;

int main()
{
    twoIntsStruct * data = NULL;
    // condition-mem-leak pattern flagged (false positive)
    // Cppcheck FP: none
    // scan-build FP: none
    data = (twoIntsStruct *)realloc(data, sizeof(twoIntsStruct));
    if(STATIC_CONST_TRUE)
    {
        free(data);
    }
}
