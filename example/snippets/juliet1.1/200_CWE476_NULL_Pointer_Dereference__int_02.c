#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B2()
{
    int * data;
    {
        {
            int tmp = 5;
            data = &tmp;
        }
        printIntLine(*data);
    }
}
#endif
