#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    twoints * data;
    {
        {
            twoints tmp;
            data = &tmp;
        }
        printIntLine(data->a);
    }
}
#endif
