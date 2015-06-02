#include "std_testcase.h"
#ifndef _WIN32
static void good2()
{
    {
    {
        long long * data = (long long *)malloc(100*sizeof(long long));
        data = (long long *)realloc(data, (130000)*sizeof(long long));
    }
    }
}
#endif
