#include "std_testcase.h"
twoIntsStruct * CWE476_NULL_Pointer_Dereference__struct_68_goodG2BData;
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__struct_68_goodG2BData = data;
}
#endif
