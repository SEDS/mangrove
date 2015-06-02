#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2BSink(int64_t * data)
{
}
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    goodG2BSink(data);
}
#endif
