#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    char * data;
    char * *dataPtr1 = &data;
    {
        free(data);
        *dataPtr1 = data;
    }
}
#endif
