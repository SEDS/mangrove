#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    wchar_t * *data_ptr1 = &data;
    {
        free(data);
        *data_ptr1 = data;
    }
}
#endif
