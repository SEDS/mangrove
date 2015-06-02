#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    long long * data;
    data = NULL;
    printLongLongLine(*data);
}
#endif
