#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G1_sink(wchar_t * data)
{
    data = (wchar_t *)malloc(100*sizeof(wchar_t));
    free(data);
    goodB2G1_sink(data);
}
#endif
