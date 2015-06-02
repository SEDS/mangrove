#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    int64_t * *dataPtr1 = &data;
    {
        {
            int64_t tmpData = 5LL;
            data = &tmpData;
        }
        *dataPtr1 = data;
    }
}
#endif
