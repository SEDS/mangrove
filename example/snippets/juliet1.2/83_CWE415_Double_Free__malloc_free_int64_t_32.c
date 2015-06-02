#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    int64_t * data;
    int64_t * *dataPtr1 = &data;
    {
        free(data);
        *dataPtr1 = data;
    }
}
#endif
