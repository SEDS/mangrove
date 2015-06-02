#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    printIntLine(*((int*)data));
}
#endif
