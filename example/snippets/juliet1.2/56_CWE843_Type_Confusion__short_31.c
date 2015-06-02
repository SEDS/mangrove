#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int intBuffer = 8;
        data = &intBuffer;
    }
    {
        void * dataCopy = data;
        void * data = dataCopy;
        printIntLine(*((int*)data));
    }
}
#endif
