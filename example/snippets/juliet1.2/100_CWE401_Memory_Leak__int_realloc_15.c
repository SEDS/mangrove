#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    int * data;
    {
        data = (int *)realloc(data, 100*sizeof(int));
    }
}
#endif
