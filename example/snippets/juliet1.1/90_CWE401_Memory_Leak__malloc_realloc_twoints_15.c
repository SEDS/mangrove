#include "std_testcase.h"
#ifndef OMITGOOD
static void good1()
{
    {
    {
        twoints * data = (twoints *)malloc(100*sizeof(twoints));
        data = (twoints *)realloc(data, (130000)*sizeof(twoints));
    }
    }
}
#endif
