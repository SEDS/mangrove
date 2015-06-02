#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G1()
{
    long long * data;
    {
        free(data);
        free(data);
    }
}
#endif
