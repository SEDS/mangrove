#include "std_testcase.h"
#ifndef OMITBAD
static void good2()
{
    {
        {
            int * data = (int *)malloc(100*sizeof(int));
            data = (int *)realloc(data, (130000)*sizeof(int));
        }
    }
}
#endif
