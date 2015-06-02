#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    int * data;
    {
        free(data);
        free(data);
    }
}
#endif
