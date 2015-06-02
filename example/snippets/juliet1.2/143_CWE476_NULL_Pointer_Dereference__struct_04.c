#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B2()
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
