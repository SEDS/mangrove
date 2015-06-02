#include "std_testcase.h"
#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__struct_54b_goodG2BSink(twoIntsStruct * data);
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__struct_54b_goodG2BSink(data);
}
#endif
