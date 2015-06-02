#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G1()
{
    wchar_t * data;
    {
        free(data);
        free(data);
    }
}
#endif
