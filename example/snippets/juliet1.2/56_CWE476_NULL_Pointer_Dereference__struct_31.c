#include "std_testcase.h"
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
