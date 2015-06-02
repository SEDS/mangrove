#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    {
        long long * data_copy = data;
        long long * data = data_copy;
        printLongLongLine(*data);
    }
}
#endif
