#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    int * data;
    {
        int tmp = 5;
        data = &tmp;
    }
    {
        int * data_copy = data;
        int * data = data_copy;
        printIntLine(*data);
    }
}
#endif
