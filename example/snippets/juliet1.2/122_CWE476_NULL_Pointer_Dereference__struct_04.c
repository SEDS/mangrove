#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    twoIntsStruct * data;
    {
        {
            twoIntsStruct tmpData;
            data = &tmpData;
        }
        printIntLine(data->intOne);
    }
}
#endif
