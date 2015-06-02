#include "std_testcase.h"
#ifndef OMITGOOD
static void goodG2B()
{
    void * data;
    {
        int buf = 8;
        data = &buf;
    }
    {
        void * data_copy = data;
        void * data = data_copy;
        printIntLine(*((int*)data));
    }
}
#endif
