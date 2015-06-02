#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B_sink(twoints * data)
{
}
static void goodG2B()
{
    twoints * data;
    {
        twoints tmp;
        data = &tmp;
    }
    goodG2B_sink(data);
}
#endif
