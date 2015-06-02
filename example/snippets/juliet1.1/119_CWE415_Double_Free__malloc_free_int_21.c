#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G2_sink(int * data)
{
    data = (int *)malloc(100*sizeof(int));
    free(data);
    goodB2G2_sink(data);
}
#endif
