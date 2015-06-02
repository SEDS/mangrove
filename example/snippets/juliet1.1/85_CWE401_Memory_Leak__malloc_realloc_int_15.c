#include "std_testcase.h"
#ifndef OMITGOOD
static void good1()
{
    {
    {
        int * data = (int *)malloc(100*sizeof(int));
        data = (int *)realloc(data, (130000)*sizeof(int));
    }
    }
}
#endif
