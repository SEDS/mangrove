#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    twoints * data;
    {
        free(data);
        free(data);
    }
}
#endif
