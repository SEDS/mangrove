#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
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
