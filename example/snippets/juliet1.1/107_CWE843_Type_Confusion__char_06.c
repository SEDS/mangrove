#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B2()
{
    void * data;
    {
        {
            char buf = 'a';
            data = &buf;
        }
    }
    printIntLine(*((int*)data));
}
#endif
