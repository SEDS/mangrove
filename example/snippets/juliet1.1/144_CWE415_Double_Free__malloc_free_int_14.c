#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    int * data;
    {
        free(data);
        free(data);
    }
}
#endif
