#include "std_testcase.h"
namespace CWE476_NULL_Pointer_Dereference__struct_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    {
        printIntLine(data->intOne);
    }
}
#endif
}
