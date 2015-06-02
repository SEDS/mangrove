#include "std_testcase.h"
#ifndef OMITBAD
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
