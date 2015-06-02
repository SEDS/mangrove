#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    int64_t * data;
    {
        {
            int64_t tmpData = 5LL;
            data = &tmpData;
        }
        printLongLongLine(*data);
    }
}
#endif
