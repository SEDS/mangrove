#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G2_sink(twoints * data)
{
    data = (twoints *)malloc(100*sizeof(twoints));
    free(data);
    goodB2G2_sink(data);
}
#endif
