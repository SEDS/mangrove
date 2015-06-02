#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    twoIntsStruct * data;
    {
        data = (twoIntsStruct *)realloc(data, 100*sizeof(twoIntsStruct));
    }
}
#endif
