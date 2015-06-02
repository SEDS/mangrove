#include "std_testcase.h"
#ifndef OMITGOOD
static void goodB2G1()
{
    char * data;
    {
        data = (char *)realloc(data, 100*sizeof(char));
    }
}
#endif
