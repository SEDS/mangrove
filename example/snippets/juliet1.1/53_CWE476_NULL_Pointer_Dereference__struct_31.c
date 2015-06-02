#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    {
        twoints * data_copy = data;
        twoints * data = data_copy;
        printIntLine(data->a);
    }
}
#endif
