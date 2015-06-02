#include "std_testcase.h"
static twoIntsStruct * CWE476_NULL_Pointer_Dereference__struct_45_goodG2BData;
#ifndef OMITGOOD
static void goodG2BSink()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__struct_45_goodG2BData = data;
}
#endif
