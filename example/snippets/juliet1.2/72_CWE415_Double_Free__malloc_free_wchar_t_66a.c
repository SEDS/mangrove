#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G()
{
    wchar_t * data;
    wchar_t * dataArray[5];
    free(data);
    dataArray[2] = data;
}
#endif
