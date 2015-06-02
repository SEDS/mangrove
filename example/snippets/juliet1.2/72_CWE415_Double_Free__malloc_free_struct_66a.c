#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    twoIntsStruct * data;
    twoIntsStruct * dataArray[5];
    free(data);
    dataArray[2] = data;
}
#endif
