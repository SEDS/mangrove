#include "std_testcase.h"
namespace CWE476_NULL_Pointer_Dereference__long_long_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    long long * data;
    {
        long long tmp = 5L;
        data = &tmp;
    }
    {
        printLongLongLine(*data);
    }
}
#endif
}
