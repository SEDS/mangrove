#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    twoIntsStruct * dataArray[5];
    {
        twoIntsStruct tmpData;
        data = &tmpData;
    }
    dataArray[2] = data;
}
#endif
