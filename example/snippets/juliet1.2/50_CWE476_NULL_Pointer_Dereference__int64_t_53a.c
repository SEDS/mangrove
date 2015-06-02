#include "std_testcase.h"
#ifndef OMITGOOD
void CWE476_NULL_Pointer_Dereference__int64_t_53b_goodG2BSink(int64_t * data);
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    CWE476_NULL_Pointer_Dereference__int64_t_53b_goodG2BSink(data);
}
#endif
