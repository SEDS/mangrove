#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    twoints * data_array[5];
    {
        twoints tmp;
        data = &tmp;
    }
    data_array[2] = data;
}
#endif
