#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    printLongLongLine(*data);
}
#endif
