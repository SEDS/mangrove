#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmpData = 5;
        data = &tmpData;
    }
    {
        int * dataCopy = data;
        int * data = dataCopy;
        printIntLine(*data);
    }
}
#endif
