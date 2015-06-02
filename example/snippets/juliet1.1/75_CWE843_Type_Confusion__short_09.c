#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B1()
{
    void * data;
    {
        {
            int buf = 8;
            data = &buf;
        }
    }
    printIntLine(*((int*)data));
}
#endif
