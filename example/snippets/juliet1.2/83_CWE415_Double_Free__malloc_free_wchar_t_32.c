#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    wchar_t * *dataPtr1 = &data;
    {
        free(data);
        *dataPtr1 = data;
    }
}
#endif
