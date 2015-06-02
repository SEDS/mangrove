#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G2_sink(char * data)
{
    data = (char *)malloc(100*sizeof(char));
    free(data);
    goodB2G2_sink(data);
}
#endif
