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
        twoIntsStruct * dataCopy = data;
        twoIntsStruct * data = dataCopy;
        printIntLine(data->intOne);
    }
}
#endif
