#include "std_testcase.h"
namespace CWE843_Type_Confusion__short_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    {
        printIntLine(*((int*)data));
    }
}
#endif
}
