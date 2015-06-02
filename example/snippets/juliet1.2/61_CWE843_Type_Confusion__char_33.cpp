#include "std_testcase.h"
namespace CWE843_Type_Confusion__char_33
{
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    {
        printIntLine(*((int*)data));
    }
}
#endif
}
