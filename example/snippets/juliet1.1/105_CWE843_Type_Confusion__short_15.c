#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B2()
{
    void * data;
    {
    {
        short buf = 8;
        data = &buf;
    }
    }
    printIntLine(*((int*)data));
}
#endif
