#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B1()
{
    wchar_t * data;
    {
        free(data);
        free(data);
    }
}
#endif
