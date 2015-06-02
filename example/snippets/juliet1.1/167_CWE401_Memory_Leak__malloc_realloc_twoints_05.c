#include "std_testcase.h"
#ifndef OMITBAD
static void good2()
{
    {
        {
            twoints * data = (twoints *)malloc(100*sizeof(twoints));
            data = (twoints *)realloc(data, (130000)*sizeof(twoints));
        }
    }
}
#endif
