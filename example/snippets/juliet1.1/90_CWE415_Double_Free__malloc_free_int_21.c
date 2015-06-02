#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G1_sink(int * data)
{
    data = (int *)malloc(100*sizeof(int));
    free(data);
    goodB2G1_sink(data);
}
#endif
