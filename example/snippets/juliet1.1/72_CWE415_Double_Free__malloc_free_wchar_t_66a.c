#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    wchar_t * data_array[5];
    free(data);
    data_array[2] = data;
}
#endif
