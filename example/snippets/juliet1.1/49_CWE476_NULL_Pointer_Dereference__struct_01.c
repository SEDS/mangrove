#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    printIntLine(data->a);
}
#endif
