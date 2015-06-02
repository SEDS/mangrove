#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
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
