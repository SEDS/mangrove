#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
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
