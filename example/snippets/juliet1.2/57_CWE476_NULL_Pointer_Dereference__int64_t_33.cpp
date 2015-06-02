#include "std_testcase.h"
namespace CWE476_NULL_Pointer_Dereference__int64_t_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    int64_t * data;
    {
        int64_t tmpData = 5LL;
        data = &tmpData;
    }
    {
        printLongLongLine(*data);
    }
}
#endif
}
