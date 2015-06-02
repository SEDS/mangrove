#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    twoints * data;
    data = NULL;
    printIntLine(data->a);
}
#endif
