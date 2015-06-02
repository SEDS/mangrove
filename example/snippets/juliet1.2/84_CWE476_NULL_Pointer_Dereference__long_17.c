#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    long * data;
    {
        {
            long tmpData = 5L;
            data = &tmpData;
        }
        printLongLine(*data);
    }
}
#endif
