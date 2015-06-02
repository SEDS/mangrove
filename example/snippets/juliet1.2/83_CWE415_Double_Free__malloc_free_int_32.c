#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    int * data;
    int * *dataPtr1 = &data;
    {
        free(data);
        *dataPtr1 = data;
    }
}
#endif
