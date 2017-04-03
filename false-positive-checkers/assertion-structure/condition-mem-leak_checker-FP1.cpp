// Juliet: CWE762_Mismatched_Memory_Management_Routines__new_array_delete_int64_t_14.cpp

#include "std_testcase.h"

int main()
{
    int64_t * data = NULL;
    // Moving the allocation code outside of the `if` statement introduces the FP for 
    // Cppcheck and scan-build.
    if(globalFive==5)
    {
        data = new int64_t[100];
    }
    // condition-mem-leak pattern flagged (false positive)
    // Cppcheck FP: none
    // scan-build FP: none
    if(globalFive==5)
    {
        delete [] data;
    }
}

