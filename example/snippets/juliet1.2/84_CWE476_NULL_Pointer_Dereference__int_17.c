#include "std_testcase.h"
#ifndef OMITBAD
static void goodG2B()
{
    int * data;
    {
        {
            int tmpData = 5;
            data = &tmpData;
        }
        printIntLine(*data);
    }
}
#endif
