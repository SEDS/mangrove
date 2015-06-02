#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    {
        int64_t * dataCopy = data;
        int64_t * data = dataCopy;
        printLongLongLine(*data);
    }
}
#endif
