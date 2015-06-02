#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    int64_t * data;
    int64_t * dataArray[5];
    free(data);
    dataArray[2] = data;
}
#endif
