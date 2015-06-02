#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    long * data;
    long * *dataPtr1 = &data;
    {
        free(data);
        *dataPtr1 = data;
    }
}
#endif
