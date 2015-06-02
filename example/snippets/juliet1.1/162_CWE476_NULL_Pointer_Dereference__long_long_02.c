#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    long long * data;
    {
        {
            long long tmp = 5L;
            data = &tmp;
        }
        printLongLongLine(*data);
    }
}
#endif
