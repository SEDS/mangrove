#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    struct _twoIntsStruct * data;
    {
        data = (struct _twoIntsStruct *)realloc(data, 100*sizeof(struct _twoIntsStruct));
    }
}
#endif
