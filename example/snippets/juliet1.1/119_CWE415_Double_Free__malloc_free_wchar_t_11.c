#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    wchar_t * data;
    {
        free(data);
        free(data);
    }
}
#endif
