#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    wchar_t * data;
    data = NULL;
    printWcharLine(data[0]);
}
#endif
