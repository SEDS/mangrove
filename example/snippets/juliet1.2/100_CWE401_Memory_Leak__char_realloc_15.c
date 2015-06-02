#include "std_testcase.h"
#ifndef OMITBAD
static void goodB2G2()
{
    char * data;
    {
        data = (char *)realloc(data, 100*sizeof(char));
    }
}
#endif
