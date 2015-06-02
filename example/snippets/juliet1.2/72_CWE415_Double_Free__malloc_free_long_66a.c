#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    long * data;
    long * dataArray[5];
    free(data);
    dataArray[2] = data;
}
#endif
