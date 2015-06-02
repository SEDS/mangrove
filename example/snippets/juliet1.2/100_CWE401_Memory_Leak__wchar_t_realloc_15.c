#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    wchar_t * data;
    {
        data = (wchar_t *)realloc(data, 100*sizeof(wchar_t));
    }
}
#endif
