#include "std_testcase.h"
namespace CWE476_NULL_Pointer_Dereference__int_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    {
        printIntLine(*data);
    }
}
#endif
}
