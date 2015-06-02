#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B2()
{
    void * data;
    {
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    }
    printIntLine(*((int*)data));
}
#endif
