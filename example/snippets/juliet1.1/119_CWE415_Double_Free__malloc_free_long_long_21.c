#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G2_sink(long long * data)
{
    data = (long long *)malloc(100*sizeof(long long));
    free(data);
    goodB2G2_sink(data);
}
#endif
