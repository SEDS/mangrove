#include "std_testcase.h"
int64_t * CWE476_NULL_Pointer_Dereference__int64_t_68_goodG2BData;
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int64_t_68_goodG2BData = data;
}
#endif
