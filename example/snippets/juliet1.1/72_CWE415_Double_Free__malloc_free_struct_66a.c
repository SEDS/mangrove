#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    twoints * data;
    twoints * data_array[5];
    free(data);
    data_array[2] = data;
}
#endif
