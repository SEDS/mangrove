#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    twoIntsStruct * data;
    {
        data = (twoIntsStruct *)realloc(data, 100*sizeof(twoIntsStruct));
    }
}
#endif
