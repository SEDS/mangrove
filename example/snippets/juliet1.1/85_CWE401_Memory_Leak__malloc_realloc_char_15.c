#include "std_testcase.h"
#ifndef OMITGOOD
static void good1()
{
    {
    {
        char * data = (char *)malloc(100*sizeof(char));
        data = (char *)realloc(data, (130000)*sizeof(char));
    }
    }
}
#endif
