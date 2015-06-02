#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    long long * data;
    {
        free(data);
        free(data);
    }
}
#endif
