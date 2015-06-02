#include "std_testcase.h"
#ifndef OMITGOOD
static void good1()
{
    {
        {
            long long * data = (long long *)malloc(100*sizeof(long long));
            data = (long long *)realloc(data, (130000)*sizeof(long long));
        }
    }
}
#endif
