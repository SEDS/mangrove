#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    int64_t * data;
    {
        data = (int64_t *)realloc(data, 100*sizeof(int64_t));
    }
}
#endif
