// Juliet: CWE401_Memory_Leak__new_array_twointsStruct_10.cpp

#include "std_testcase.h"

int main()
{
    twoIntsStruct * data = NULL;
    // Bringing the allocation code outside the `if` statement AND removing
    // the printStructLine() call introduces the Cppcheck FP.
    if(globalTrue)
    {
        data = new twoIntsStruct[100];
        // Removing the printStructLine() call introduces the scan-build FP.
        printStructLine(&data[0]);
    }
    // condition-mem-leak pattern flagged (false positive)
    // scan-build FP: none
    // Cppcheck FP: none
    if(globalFalse)
    {
    }
    else
    {
        delete[] data;
    }
}
