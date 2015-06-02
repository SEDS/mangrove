#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoIntsStruct * data;
    twoIntsStruct * *dataPtr1 = &data;
    {
        {
            twoIntsStruct tmpData;
            data = &tmpData;
        }
        *dataPtr1 = data;
    }
}
#endif
