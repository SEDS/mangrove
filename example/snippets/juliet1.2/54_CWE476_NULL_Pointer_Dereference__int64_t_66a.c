#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    int64_t * dataArray[5];
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    dataArray[2] = data;
}
#endif
