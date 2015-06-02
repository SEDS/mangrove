#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G()
{
    twoIntsStruct * data;
    {
        data = (twoIntsStruct *)realloc(data, 100*sizeof(twoIntsStruct));
    }
}
#endif
