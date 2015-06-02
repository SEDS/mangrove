#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    int * data;
    data = NULL;
    printIntLine(*data);
}
#endif
