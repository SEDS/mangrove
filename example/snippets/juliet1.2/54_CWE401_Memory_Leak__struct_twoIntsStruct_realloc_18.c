#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G()
{
    struct _twoIntsStruct * data;
    data = (struct _twoIntsStruct *)realloc(data, 100*sizeof(struct _twoIntsStruct));
}
#endif
