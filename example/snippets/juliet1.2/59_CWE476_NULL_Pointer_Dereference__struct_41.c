#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2BSink(twoIntsStruct * data)
{
}
static void goodG2B()
{
    twoIntsStruct * data;
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    goodG2BSink(data);
}
#endif
