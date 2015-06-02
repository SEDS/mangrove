#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G()
{
    wchar_t * data;
    {
        data = (wchar_t *)realloc(data, 100*sizeof(wchar_t));
    }
}
#endif
