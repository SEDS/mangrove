#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    long long * data;
    {
        free(data);
        free(data);
    }
}
#endif
